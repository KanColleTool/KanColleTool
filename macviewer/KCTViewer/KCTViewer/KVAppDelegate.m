//
//  KVAppDelegate.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 MacaroniCode. All rights reserved.
//

#import "KVAppDelegate.h"
#import "KVHTTPProtocol.h"
#import "KVCachingHTTPProtocol.h"
#import "KVTranslator.h"
#import "NSURL+KVUtil.h"

@interface KVAppDelegate ()

- (void)generateAPILink;
- (void)updateBrowserLink;

@end

@implementation KVAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	// Register custom URL protocols; the order matters, as they're handled in reverse order of registration
	// In this case, the meddling protocol will get predecence over the caching one, like it should be
	[NSURLProtocol registerClass:[KVCachingHTTPProtocol class]];
	[NSURLProtocol registerClass:[KVHTTPProtocol class]];
	
	// For all our out-of-browser networking needs
	self.manager = [AFHTTPRequestOperationManager manager];
	self.manager.responseSerializer.acceptableContentTypes = [self.manager.responseSerializer.acceptableContentTypes setByAddingObject:@"application/octet-stream"];

	// No, we don't want the web view to scroll just a few pixels up and down.
	[self.webView.mainFrame.frameView setAllowsScrolling:NO];

	// Needed in Mavericks for Flash to render correctly.
	[self.webView setLayerUsesCoreImageFilters:YES];

	// Treat the web view as a web browser; this makes it cache a whole lot more
	[[WebPreferences standardPreferences] setCacheModel:WebCacheModelPrimaryWebBrowser];

	// Set up a cache; without this, loading the game will be slow as hell
	NSString *cachePath = [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"KCTViewer"];
	NSURLCache *cache = [[NSURLCache alloc] initWithMemoryCapacity:20 * 1024 * 1024
													  diskCapacity:100 * 1024 * 1024
														  diskPath:cachePath];
	[NSURLCache setSharedURLCache:cache];
	
	// Attempt to retrieve stored server and API Token
	self.server = [[NSUserDefaults standardUserDefaults] valueForKey:@"server"];
	self.apiToken = [[NSUserDefaults standardUserDefaults] valueForKey:@"apiToken"];
	
	// Check for updates
	[self checkForUpdates];
	
	// If we don't have them, ask for a link.
	// Otherwise, load the the translation right away, which will end up using it.
	if(!self.server || !self.apiToken)
		[self actionEnterAPILink:nil];
	else
		[self loadTranslation];
}

- (void)checkForUpdates
{
	AFHTTPRequestOperation *op = [[AFHTTPRequestOperation alloc] initWithRequest:
								  [NSURLRequest requestWithURL:[NSURL URLWithString:@"http://kancolletool.github.io/VERSION"]]];
	[op setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation, id responseObject) {
		NSString *newVersion = [[NSString alloc] initWithData:responseObject encoding:NSUTF8StringEncoding];
		NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] valueForKey:@"CFBundleShortVersionString"];
		
		BOOL outdated = ([newVersion compare:appVersion options:NSNumericSearch] == NSOrderedDescending);
		if(outdated)
		{
			[[NSAlert alertWithMessageText:@"New Version Available" defaultButton:@"Download" alternateButton:@"Ignore" otherButton:nil informativeTextWithFormat:@"Version %@ has been released, and is available for download.", newVersion] beginSheetModalForWindow:_window completionHandler:^(NSModalResponse returnCode) {
				if(returnCode == NSAlertDefaultReturn)
					[[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://kancolletool.github.io/downloads/"]];
			}];
		}
	} failure:^(AFHTTPRequestOperation *operation, NSError *error) {
		NSLog(@"Couldn't check for updates! %@", error);
	}];
	[op start];
}

- (void)loadTranslation
{
	// Center the loading window over the main window
	[_loadingTranslationWindow setFrame:NSMakeRect(_window.frame.origin.x +
												   (_window.frame.size.width - _loadingTranslationWindow.frame.size.width)/2,
												   _window.frame.origin.y +
												   (_window.frame.size.height - _loadingTranslationWindow.frame.size.height)/2,
												   _loadingTranslationWindow.frame.size.width,
												   _loadingTranslationWindow.frame.size.height) display:YES];
	
	// Show the window and start animating the progress bar
	[_window beginSheet:_loadingTranslationWindow completionHandler:NULL];
	[_translationLoadingBar startAnimation:self];
	
	// Get the English translation from the server
	[_manager GET:@"http://api.comeonandsl.am/translation/en/" parameters:nil
		  success:^(AFHTTPRequestOperation *operation, id responseObject) {
			  
			  // responseObject is a dictionary, unless something is really wrong here
			  // (see: undetected Captive Portal)
			  NSDictionary *res = responseObject;
			  if(![[res objectForKey:@"success"] isEqual:[NSNumber numberWithInt:1]])
			  {
				  [[NSAlert alertWithMessageText:@"Translation API returned an error" defaultButton:@"Retry" alternateButton:@"Continue" otherButton:nil informativeTextWithFormat:@"The Translation API doesn't seem to be working. You can continue without translation data, but the game will be in Japanese. Continue?"] beginSheetModalForWindow:_window completionHandler:^(NSModalResponse returnCode) {
					  if(returnCode == NSAlertDefaultReturn) [self loadTranslation];
				  }];
			  }
			  else
			  {
				  [[KVTranslator sharedTranslator] setTldata:[res objectForKey:@"translation"]];
			  }
			  
			  [self loadTranslationFinished];
			  
		  } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
			  
			  [[NSAlert alertWithMessageText:@"Failed to load Translation Data" defaultButton:@"Retry" alternateButton:@"Continue" otherButton:nil informativeTextWithFormat:@"This usually means that your connection is down, or that the translation API is. You can continue without this, but the game will be in Japanese. Continue?"] beginSheetModalForWindow:self.window completionHandler:^(NSModalResponse returnCode) {
				  if(returnCode == NSAlertDefaultReturn) [self loadTranslation];
			  }];
			  
			  [self loadTranslationFinished];
			  
		  }];
}

- (void)loadTranslationFinished
{
	[_window endSheet:_loadingTranslationWindow];
	[_translationLoadingBar stopAnimation:self];
	[self generateAPILink];
	[self loadBundledIndex];
}

- (void)loadBundledIndex
{
	NSError *error = nil;
	NSString *html = [NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"index" ofType:@"html"]
											   encoding:NSUTF8StringEncoding error:&error];
	if(error)
	{
		[[NSAlert alertWithError:error] beginSheetModalForWindow:self.window completionHandler:^(NSModalResponse returnCode) {
			[[NSApplication sharedApplication] terminate:self];
		}];
	}
	else
	{
		[[self.webView mainFrame] loadHTMLString:html baseURL:self.apiLink];
	}
}

- (void)actionCheckForUpdates:(id)sender
{
	[self checkForUpdates];
}

- (void)actionEnterAPILink:(id)sender
{
	[self.window beginSheet:self.enterAPILinkWindow completionHandler:^(NSModalResponse returnCode) {
		// Ignore Cancel presses
		if(returnCode == NSModalResponseOK)
		{
			NSURL *url = [NSURL URLWithString:[self.apiLinkField stringValue]];
			self.server = url.host;
			self.apiToken = [[url queryItems] objectForKey:@"api_token"];
			
			[[NSUserDefaults standardUserDefaults] setObject:self.server forKey:@"server"];
			[[NSUserDefaults standardUserDefaults] setObject:self.apiToken forKey:@"apiToken"];
			[[NSUserDefaults standardUserDefaults] synchronize];
			
			// Sync the settings to the tool
			NSUserDefaults *toolSettings = [[NSUserDefaults alloc] initWithSuiteName:@"com.macaronicode.KanColleTool"];
			[toolSettings setValuesForKeysWithDictionary:[[NSUserDefaults standardUserDefaults] dictionaryRepresentation]];
			[toolSettings synchronize];
			
			[self loadTranslation];
		}
	}];
}

- (IBAction)actionClearCache:(id)sender
{
	[[NSURLCache sharedURLCache] removeAllCachedResponses];
	[[NSFileManager defaultManager] removeItemAtPath:[KVCachingHTTPProtocol cacheDir] error:NULL];
	[self loadBundledIndex];
}

- (void)actionAPILinkEntered:(id)sender
{
	[self.window endSheet:self.enterAPILinkWindow returnCode:NSModalResponseOK];
	[self updateBrowserLink];
}

- (void)actionAPILinkCanceled:(id)sender
{
	[self.window endSheet:self.enterAPILinkWindow returnCode:NSModalResponseCancel];
}

- (void)generateAPILink
{
	self.apiLink = [NSURL URLWithString:[NSString stringWithFormat:@"http://%@/kcs/mainD2.swf?api_token=%@", self.server, self.apiToken]];
}

- (void)updateBrowserLink
{
	NSLog(@"Server: %@", self.server);
	NSLog(@"API Token: %@", self.apiToken);
	NSLog(@"API Link: %@", self.apiLink);
	[self.webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"setAPILink(\"%@\"); null", self.apiLink]];
}

- (void)webView:(WebView *)sender didFinishLoadForFrame:(WebFrame *)frame
{
	[self updateBrowserLink];
}

- (NSUInteger)webView:(WebView *)webView dragDestinationActionMaskForDraggingInfo:(id<NSDraggingInfo>)draggingInfo
{
	return WebDragDestinationActionNone;
}

- (id)webView:(WebView *)sender identifierForInitialRequest:(NSURLRequest *)request fromDataSource:(WebDataSource *)dataSource
{
	return request.URL;
}

#if DEBUG
- (NSURLRequest *)webView:(WebView *)sender resource:(id)identifier willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)redirectResponse fromDataSource:(WebDataSource *)dataSource
{
	NSLog(@"-> %@", identifier);
	return request;
}

- (void)webView:(WebView *)sender resource:(id)identifier didFinishLoadingFromDataSource:(WebDataSource *)dataSource
{
	NSLog(@"<- %@", identifier);
}

- (void)webView:(WebView *)sender resource:(id)identifier didFailLoadingWithError:(NSError *)error fromDataSource:(WebDataSource *)dataSource
{
	NSLog(@"xx %@:\n%@", identifier, error);
}
#endif

@end
