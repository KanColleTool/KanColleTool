//
//  KVHTTPProtocol.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-15.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import "KVHTTPProtocol.h"
#import "KVTranslator.h"

@implementation KVHTTPProtocol

+ (BOOL)canInitWithRequest:(NSURLRequest *)request
{
	return [request.URL.scheme isEqualToString:@"http"] && [request.HTTPMethod isEqualToString:@"POST"] && ![[self class] propertyForKey:@"_handled" inRequest:request];
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
	self.interesting = [self.request.URL.path hasPrefix:@"/kcsapi"];
	self.connection = [NSURLConnection connectionWithRequest:self.request delegate:self];
}

- (void)stopLoading
{
	[self.connection cancel];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
	if(!self.interesting)
		[self.client URLProtocol:self didLoadData:data];
	else
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
		[self deliverResponse];
	
	/*for(NSString *key in [(NSHTTPURLResponse*)response allHeaderFields])
		NSLog(@"%@ : %@", key, [[(NSHTTPURLResponse*)response allHeaderFields] objectForKey:key]);*/
	[self.client URLProtocol:self didReceiveResponse:response
		  cacheStoragePolicy:([self.request.URL.path hasPrefix:@"/kcsapi"] ? NSURLCacheStorageNotAllowed : NSURLCacheStorageAllowed)];
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
	// Deliver buffered data
	[self deliverResponse];
	
	// Tell the client the request is finished
	[self.client URLProtocolDidFinishLoading:self];
	self.connection = nil;
}

- (void)deliverResponse
{
	if(self.buffer)
	{
		// This should always be true (we shouldn't have a buffer if the request is not interesting,
		// but it's always good to check a second time. That might change in the future or something.
		if([self isInteresting])
		{
			// str is the buffer converted into a string, outstr is the output buffer
			NSString *str = [[NSString alloc] initWithData:self.buffer encoding:NSUTF8StringEncoding];
			NSMutableString *outstr = [[NSMutableString alloc] init];
			
			// Build an expression matching any string-string key-valye pairs in a JSON file
			NSError *error = nil;
			NSRegularExpression *exp = [[NSRegularExpression alloc] initWithPattern:@"\"([^\"]+)\"\\s*:\\s*\"([^\"]+)\"" options:0 error:&error];
			if(error) NSLog(@"Expression Error: %@", exp);
			
			// Find all matches in the string, this gives us an array of NSTextCheckingResult*
			NSArray *matches = [exp matchesInString:str options:0 range:NSMakeRange(0, [str length])];
			
			// lastEnd is where the last chunk we added to the string ended
			NSUInteger lastEnd = 0;
			
			// Loop through all the matches to replace them
			for(NSTextCheckingResult *result in matches)
			{
				// Since we found a match, that means we most likely skipped a chunk of data that's
				// most likely important. So push that chunk and mark its end to keep from repeating it.
				[outstr appendString:[str substringWithRange:NSMakeRange(lastEnd, result.range.location - lastEnd)]];
				lastEnd = result.range.location + result.range.length;
				
				// Extract the key and value to be able to match on them; later, only the value will
				// really be used (its CRC32 is the key to the translation data), but the key is good
				// to have anyways, for debugging and such.
				NSString *key = [str substringWithRange:[result rangeAtIndex:1]];
				NSString *value = [str substringWithRange:[result rangeAtIndex:2]];
				value = [[KVTranslator sharedTranslator] translate:value];
				
				// JSONify this key-value pair and push it too
				[outstr appendFormat:@"\"%@\":\"%@\"", key, value];
			}
			
			// Push the remaining stuff at the end
			[outstr appendString:[str substringFromIndex:lastEnd]];
			
			// Feed the client the resulting data
			[self.client URLProtocol:self didLoadData:[outstr dataUsingEncoding:NSUTF8StringEncoding]];
		}
		// If this request is uninteresting, just feed the client the buffer, and wonder why
		// the heck we buffered the response in the first place.
		else
			[self.client URLProtocol:self didLoadData:self.buffer];
		
		// Because properties' magical reference counting, this also releases the buffer
		self.buffer = nil;
	}
}

@end
