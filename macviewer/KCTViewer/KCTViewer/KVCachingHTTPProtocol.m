//
//  KVCachingHTTPProtocol.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-23.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import "KVCachingHTTPProtocol.h"
#import "NSString+KVHashes.h"

@implementation KVCachingHTTPProtocol

+ (BOOL)canInitWithRequest:(NSURLRequest *)request
{
	return [request.URL.scheme isEqualToString:@"http"] &&	// Only handle HTTP Requests...
			[request.HTTPMethod isEqualToString:@"GET"] &&	// ...GETs, more specifically...
			![request.URL.host isEqualToString:@"http://api.comeonandsl.am"] &&	// ...that aren't to the API...
			![[self class] propertyForKey:@"_handled" inRequest:request];		// ...and that aren't already handled.
}

+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request
{
	return request;
}

- (id)initWithRequest:(NSURLRequest *)request cachedResponse:(NSCachedURLResponse *)cachedResponse client:(id<NSURLProtocolClient>)client
{
	return [super initWithRequest:[request mutableCopy] cachedResponse:cachedResponse client:client];
}

- (void)startLoading
{
	[[self class] setProperty:[NSNumber numberWithBool:YES] forKey:@"_handled" inRequest:(NSMutableURLRequest*)self.request];
	
	if([[NSFileManager defaultManager] fileExistsAtPath:[self cachePath]])
	{
		self.cacheEntry = [NSKeyedUnarchiver unarchiveObjectWithFile:[self cachePath]];
		[self.client URLProtocol:self didReceiveResponse:self.cacheEntry.response cacheStoragePolicy:NSURLCacheStorageNotAllowed];
		[self.client URLProtocol:self didLoadData:self.cacheEntry.data];
		[self.client URLProtocolDidFinishLoading:self];
	}
	else
	{
		self.cacheEntry = [[KVCacheEntry alloc] initWithRequest:self.request];
		self.connection = [NSURLConnection connectionWithRequest:self.request delegate:self];
	}
}

- (void)stopLoading
{
	[self.connection cancel];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
	[self.cacheEntry appendData:data];
	[self.client URLProtocol:self didLoadData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
	[self.client URLProtocol:self didFailWithError:error];
	self.connection = nil;
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
	if(self.cacheEntry.response)
	{
		[NSKeyedArchiver archiveRootObject:self.cacheEntry toFile:[self cachePath]];
		self.cacheEntry = [[KVCacheEntry alloc] initWithRequest:self.request];
	}
	
	self.cacheEntry.response = response;
	[self.client URLProtocol:self didReceiveResponse:response cacheStoragePolicy:NSURLCacheStorageNotAllowed];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
	[NSKeyedArchiver archiveRootObject:self.cacheEntry toFile:[self cachePath]];
	[self.client URLProtocolDidFinishLoading:self];
	self.connection = nil;
}

- (NSString *)cachePath
{
	if(!_cachePath)
	{
		NSFileManager *fm = [[NSFileManager alloc] init];
		
		NSString *cacheID = [[self.request.URL absoluteString] sha1];
		NSString *cacheDir = [[[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"KCTViewer"] stringByAppendingPathComponent:@"ProtocolCache"];
		BOOL cacheDirIsDir;
		
		if(![fm fileExistsAtPath:cacheDir isDirectory:&cacheDirIsDir] || !cacheDirIsDir)
		{
			if(!cacheDirIsDir) [fm removeItemAtPath:cacheDir error:NULL];
			[fm createDirectoryAtPath:cacheDir withIntermediateDirectories:YES attributes:nil error:NULL];
		}
		
		_cachePath = [cacheDir stringByAppendingPathComponent:cacheID];
		NSLog(@"Cache Path: %@", _cachePath);
	}
	
	return _cachePath;
}

@end
