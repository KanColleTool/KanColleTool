//
//  KVJSUtils.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-15.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <WebKit/WebKit.h>

@interface KVJSUtils : NSObject

- (void)attachToScriptObject:(WebScriptObject *)so;

- (void)consoleLog:(id)msg;

@end
