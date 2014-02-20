//
//  KVAppDelegate.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 the KanColleTool team. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>

@interface KVAppDelegate : NSObject <NSApplicationDelegate>

@property (nonatomic, strong) NSString *server, *apiToken;
@property (nonatomic, strong) NSURL *apiLink;

@property (nonatomic, strong) AFHTTPRequestOperationManager *manager;

@property (assign) IBOutlet NSWindow *window, *enterAPILinkWindow, *loadingTranslationWindow;
@property (assign) IBOutlet NSProgressIndicator *translationLoadingBar;
@property (assign) IBOutlet WebView *webView;
@property (assign) IBOutlet NSTextField *apiLinkField;

- (void)checkForUpdates;
- (void)loadTranslation;
- (void)loadTranslationFinished;
- (void)loadBundledIndex;

- (IBAction)actionCheckForUpdates:(id)sender;
- (IBAction)actionEnterAPILink:(id)sender;
- (IBAction)actionClearCache:(id)sender;
- (IBAction)actionReset:(id)sender;
- (IBAction)actionAPILinkEntered:(id)sender;
- (IBAction)actionAPILinkCanceled:(id)sender;

@end
