//
//  KVAppDelegate.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 MacaroniCode. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>

@interface KVAppDelegate : NSObject <NSApplicationDelegate>

@property (nonatomic, strong) NSString *server, *apiToken;
@property (nonatomic, strong) NSURL *apiLink;

@property (assign) IBOutlet NSWindow *window, *enterAPILinkWindow;
@property (assign) IBOutlet WebView *webView;
@property (assign) IBOutlet NSTextField *apiLinkField;

- (IBAction)actionEnterAPILink:(id)sender;
- (IBAction)actionAPILinkEntered:(id)sender;
- (IBAction)actionAPILinkCanceled:(id)sender;

@end
