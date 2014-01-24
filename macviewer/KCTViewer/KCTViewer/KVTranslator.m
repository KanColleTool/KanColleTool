//
//  KVTranslator.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-21.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import "KVTranslator.h"
#import "NSString+KVHashes.h"

@implementation KVTranslator

+ (instancetype)sharedTranslator
{
	static dispatch_once_t pred;
    static KVTranslator *sharedInstance = nil;
    dispatch_once(&pred, ^{
        sharedInstance = [[KVTranslator alloc] init];
    });
	
    return sharedInstance;
}

- (NSString *)translate:(NSString *)line
{
	// Use CFStringTransform to unescape the line
	NSMutableString *unescapedLine = [line mutableCopy];
	CFStringTransform((__bridge CFMutableStringRef)unescapedLine, NULL, CFSTR("Any-Hex/Java"), YES);
	
	// Look up a translation
	NSString *translation = [self.tldata objectForKey:[NSString stringWithFormat:@"%lu", [unescapedLine crc32]]];
	
	if(translation)
	{
		NSLog(@"TL: %@ -> %@", unescapedLine, translation);
		
		// Escape the translated line, in case it contains non-ASCII characters
		translation = [translation mutableCopy];
		CFStringTransform((__bridge CFMutableStringRef)translation, NULL, CFSTR("Any-Hex/Java"), NO);
		
		return translation;
	}
	else
	{
		NSLog(@"No TL: %@", unescapedLine);
		return line;
	}
}

@end
