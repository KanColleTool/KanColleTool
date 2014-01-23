//
//  KVCachingHTTPProtocol.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-23.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KVCacheEntry.h"

@interface KVCachingHTTPProtocol : NSURLProtocol
{
	NSString *_cachePath;
}

@property (nonatomic, strong) NSURLConnection *connection;
@property (nonatomic, strong) KVCacheEntry *cacheEntry;

- (id)initWithRequest:(NSURLRequest *)request cachedResponse:(NSCachedURLResponse *)cachedResponse client:(id<NSURLProtocolClient>)client;
+ (BOOL)canInitWithRequest:(NSURLRequest *)request;
+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request;

- (NSString *)cachePath;

- (void)startLoading;
- (void)stopLoading;

@end
