//
//  NSURL+KVUtil.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 the KanColleTool team. All rights reserved.
//

#import "NSURL+KVUtil.h"

@implementation NSURL (KVUtil)

- (NSDictionary *)queryItems
{
	NSMutableDictionary *items = [[NSMutableDictionary alloc] init];
	
	// Split the string by '&'...
	for (NSString *component in [self.query componentsSeparatedByString:@"&"]) {
		// ...then those parts by '='.
		NSArray *halves = [component componentsSeparatedByString:@"="];
		
		// Skip over invalid items with too many = signs, and treat keys with no
		// values as having an empty string for a value.
		if([halves count] == 2)
			[items setObject:[[halves lastObject] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding] forKey:[halves firstObject]];
		else if([halves count] == 1)
			[items setObject:@"" forKey:[halves firstObject]];
		else continue;
	}
	
	return items;
}

@end
