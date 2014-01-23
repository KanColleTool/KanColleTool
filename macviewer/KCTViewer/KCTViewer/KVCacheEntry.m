//
//  KVCacheEntry.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-23.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import "KVCacheEntry.h"

@implementation KVCacheEntry

- (id)initWithRequest:(NSURLRequest *)request
{
	if((self = [super init]))
	{
		self.request = request;
		self.data = [NSMutableData data];
	}
	
	return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
	if((self = [super init]))
	{
		self.request = [aDecoder decodeObjectForKey:@"request"];
		self.response = [aDecoder decodeObjectForKey:@"response"];
		self.data = [aDecoder decodeObjectForKey:@"data"];
	}
	
	return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder
{
	[aCoder encodeObject:self.request forKey:@"request"];
	[aCoder encodeObject:self.response forKey:@"response"];
	[aCoder encodeObject:self.data forKey:@"data"];
}

- (void)appendData:(NSData *)data
{
	[self.data appendData:data];
}

@end
