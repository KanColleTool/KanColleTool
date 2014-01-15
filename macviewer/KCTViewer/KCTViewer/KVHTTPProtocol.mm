//
//  KVHTTPProtocol.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-15.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import "KVHTTPProtocol.h"

@implementation KVHTTPProtocol

+ (BOOL)canInitWithRequest:(NSURLRequest *)request
{
	// Only intercept HTTP requests that start with "/kcsapi".
	return [request.URL.scheme isEqualToString:@"http"] && [request.URL.path hasPrefix:@"/kcsapi"] && ![[self class] propertyForKey:@"_handled" inRequest:request];
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
	self.connection = [NSURLConnection connectionWithRequest:self.request delegate:self];
}

- (void)stopLoading
{
	[self.connection cancel];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
	//[self.client URLProtocol:self didLoadData:data];
	if(!self.buffer) self.buffer = [[NSMutableData alloc] initWithData:data];
	else [self.buffer appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
	[self.client URLProtocol:self didFailWithError:error];
	self.connection = nil;
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
	// In the case of multipart requests, this may be called several times, in which case the
	// docs say we should empty the buffer before delivering the new response.
	if([self.buffer length] > 0)
	{
		[self.client URLProtocol:self didLoadData:self.buffer];
		self.buffer = nil;
	}
	
	[self.client URLProtocol:self didReceiveResponse:response cacheStoragePolicy:NSURLCacheStorageNotAllowed];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
	// Deliver buffered data
	[self.client URLProtocol:self didLoadData:self.buffer];
	self.buffer = nil;
	
	// Tell the client the request is finished
	[self.client URLProtocolDidFinishLoading:self];
	self.connection = nil;
}

@end
