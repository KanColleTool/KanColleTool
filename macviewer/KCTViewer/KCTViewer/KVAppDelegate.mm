//
//  KVAppDelegate.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 MacaroniCode. All rights reserved.
//

#import "KVAppDelegate.h"
#import "KVHTTPProtocol.h"
#import "NSURL+KVUtil.h"

@interface KVAppDelegate ()

- (void)generateAPILink;
- (void)updateBrowserLink;

@end

@implementation KVAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	// Register a custom URL Protocol to mess with the responses
	[NSURLProtocol registerClass:[KVHTTPProtocol class]];
	
	// No, we don't want the web view to scroll just a few pixels up and down.
	[self.webView.mainFrame.frameView setAllowsScrolling:NO];
	
	// Needed in Mavericks for Flash to render correctly.
    	[self.webView setLayerUsesCoreImageFilters: YES];
	
	// Treat the web view as a web browser; this makes it cache a whole lot more
	[[WebPreferences standardPreferences] setCacheModel:WebCacheModelPrimaryWebBrowser];
	
	// Set up a cache; without this, loading the game will be slow as hell
	NSString *cachePath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject];
	NSURLCache *cache = [[NSURLCache alloc] initWithMemoryCapacity:20 * 1024 * 1024
													  diskCapacity:100 * 1024 * 1024
														  diskPath:cachePath];
	[NSURLCache setSharedURLCache:cache];
	
	// Attempt to retrieve stored server and API Token
	self.server = [[NSUserDefaults standardUserDefaults] valueForKey:@"server"];
	self.apiToken = [[NSUserDefaults standardUserDefaults] valueForKey:@"apiToken"];
	
	// If we don't have them, ask for a link
	if(!self.server || !self.apiToken)
	{
		[self actionEnterAPILink:nil];
	}
	// Otherwise, generate a link and load it
	else
	{
		[self generateAPILink];
		[self loadBundledIndex];
	}
	
	NSLog(@"Server: %@", self.server);
	NSLog(@"API Token: %@", self.apiToken);
	NSLog(@"API Link: %@", self.apiLink);
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

- (void)loadJS
{
	if(!self.jsUtils)
		self.jsUtils = [[KVJSUtils alloc] init];
	
	[self.jsUtils attachToScriptObject:self.webView.windowScriptObject];
	[self loadScript:@"esc"];
}

- (WebScriptObject *)loadScript:(NSString *)name
{
	NSString *path = [[NSBundle mainBundle] pathForResource:name ofType:@"js"];
	if(!path)
	{
		[NSAlert alertWithMessageText:@"Couldn't find JS File" defaultButton:@"Ok" alternateButton:nil otherButton:nil informativeTextWithFormat:@"Looks like we couldn't find %@.js... This will most likely break things.\nIf you have the file conveniently at hand, please put it in my /Contents/Resources folder and restart.", name];
	}
	
	NSError *error = nil;
	NSString *js = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&error];
	
	if(error)
	{
		[[NSAlert alertWithError:error] runModal];
		return nil;
	}
	else return [self.webView.windowScriptObject evaluateWebScript:js];
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
			[self generateAPILink];
			[self updateBrowserLink];
			
			[[NSUserDefaults standardUserDefaults] setObject:self.server forKey:@"server"];
			[[NSUserDefaults standardUserDefaults] setObject:self.apiToken forKey:@"apiToken"];
			[[NSUserDefaults standardUserDefaults] synchronize];
		}
	}];
}

- (IBAction)actionClearCache:(id)sender
{
	[[NSURLCache sharedURLCache] removeAllCachedResponses];
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
	[self.webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"setAPILink(\"%@\"); null", self.apiLink]];
}

- (void)webView:(WebView *)sender didFinishLoadForFrame:(WebFrame *)frame
{
	[self loadJS];
	[self updateBrowserLink];
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
