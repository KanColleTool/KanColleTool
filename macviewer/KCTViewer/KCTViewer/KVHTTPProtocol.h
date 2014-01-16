//
//  KVHTTPProtocol.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-15.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KVHTTPProtocol : NSURLProtocol <NSURLConnectionDelegate,NSURLConnectionDataDelegate>

@property (nonatomic, strong) NSURLConnection *connection;
@property (nonatomic, strong) NSMutableData *buffer;

- (id)initWithRequest:(NSURLRequest *)request cachedResponse:(NSCachedURLResponse *)cachedResponse client:(id<NSURLProtocolClient>)client;
+ (BOOL)canInitWithRequest:(NSURLRequest *)request;
+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request;

- (void)startLoading;
- (void)stopLoading;

- (void)deliverResponse;

@end
