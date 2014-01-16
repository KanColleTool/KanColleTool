//
//  KVJSUtils.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-15.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import "KVJSUtils.h"

@implementation KVJSUtils

+ (BOOL)isSelectorExcludedFromWebScript:(SEL)selector
{
	return !(selector == @selector(consoleLog:));
}

- (void)attachToScriptObject:(WebScriptObject *)so
{
	[so setValue:self forKey:@"kvu"];
	[so evaluateWebScript:@"console = { log: function(msg) { kvu.consoleLog_(msg); } }"];
}

- (void)consoleLog:(id)msg
{
	if([msg isKindOfClass:[WebScriptObject class]])
		msg = [(WebScriptObject*)msg stringRepresentation];
	NSLog(@"J> %@", msg);
}

@end
