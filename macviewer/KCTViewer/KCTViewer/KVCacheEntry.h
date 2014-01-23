//
//  KVCacheEntry.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-23.
//  Copyright (c) 2014 MacaroniCode. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KVCacheEntry : NSObject <NSCoding>

@property (nonatomic, strong) NSURLRequest *request;
@property (nonatomic, strong) NSURLResponse *response;
@property (nonatomic, strong) NSMutableData *data;

- (id)initWithRequest:(NSURLRequest *)request;
- (id)initWithCoder:(NSCoder *)aDecoder;
- (void)encodeWithCoder:(NSCoder *)aCoder;

- (void)appendData:(NSData *)data;

@end
