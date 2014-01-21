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

- (id)init
{
	if((self = [super init]))
	{
		NSError *error = nil;
		NSString *tljson = [NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"kc_eng" ofType:@"json"]
													 encoding:NSUTF8StringEncoding error:&error];
		if(error)
		{
			NSLog(@"Couldn't read kc_eng.json: %@", error);
			return nil;
		}
		
		self.tldata = [NSJSONSerialization JSONObjectWithData:[tljson dataUsingEncoding:NSUTF8StringEncoding] options:0 error:&error];
		if(error)
		{
			NSLog(@"kc_eng.json is invalid: %@", error);
			return nil;
		}
	}
	
	return self;
}

- (NSString *)translate:(NSString *)line
{
	// Use CFStringTransform to unescape the line
	NSMutableString *unescapedLine = [line mutableCopy];
	CFStringTransform((__bridge CFMutableStringRef)unescapedLine, NULL, CFSTR("Any-Hex/Java"), YES);
	
	// Look up a translation
	NSString *translation = [self.tldata objectForKey:[NSString stringWithFormat:@"%d", [unescapedLine s_crc32]]];
	
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
