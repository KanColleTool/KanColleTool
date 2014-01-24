//
//  KVAppDelegate.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 MacaroniCode. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#import "KVJSUtils.h"

@interface KVAppDelegate : NSObject <NSApplicationDelegate>

@property (nonatomic, strong) NSString *server, *apiToken;
@property (nonatomic, strong) NSURL *apiLink;

@property (nonatomic, strong) KVJSUtils *jsUtils;
@property (nonatomic, strong) AFHTTPRequestOperationManager *manager;

@property (assign) IBOutlet NSWindow *window, *enterAPILinkWindow, *loadingTranslationWindow;
@property (assign) IBOutlet NSProgressIndicator *translationLoadingBar;
@property (assign) IBOutlet WebView *webView;
@property (assign) IBOutlet NSTextField *apiLinkField;

- (void)loadTranslation;
- (void)loadTranslationFinished;
- (void)loadBundledIndex;
- (void)loadJS;
- (WebScriptObject *)loadScript:(NSString *)name;

- (IBAction)actionEnterAPILink:(id)sender;
- (IBAction)actionClearCache:(id)sender;
- (IBAction)actionAPILinkEntered:(id)sender;
- (IBAction)actionAPILinkCanceled:(id)sender;

@end
