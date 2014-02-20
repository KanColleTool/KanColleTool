//
//  NSString+KVHashes.m
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-21.
//  Copyright (c) 2014 the KanColleTool team. All rights reserved.
//

#import "NSString+KVHashes.h"
#import <CommonCrypto/CommonDigest.h>
#import <zlib.h>

@implementation NSString (KVHashes)

- (NSString *)sha1
{
	NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
	
	unsigned char digest[CC_SHA1_DIGEST_LENGTH];
	CC_SHA1(data.bytes, (CC_LONG)data.length, digest);
	
	NSMutableString *digestString = [[NSMutableString alloc] initWithCapacity:CC_SHA1_DIGEST_LENGTH*2];
	for(int i = 0; i < CC_SHA1_DIGEST_LENGTH; i++)
		[digestString appendFormat:@"%02x", digest[i]];
	
	return digestString;
}

- (NSString *)sha256
{
	NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
	
	unsigned char digest[CC_SHA256_DIGEST_LENGTH];
	CC_SHA256(data.bytes, (CC_LONG)data.length, digest);
	
	NSMutableString *digestString = [[NSMutableString alloc] initWithCapacity:CC_SHA256_DIGEST_LENGTH*2];
	for(int i = 0; i < CC_SHA256_DIGEST_LENGTH; i++)
		[digestString appendFormat:@"%02x", digest[i]];
	
	return digestString;
}

- (unsigned long)crc32
{
	NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
	return crc32(0, data.bytes, (uint32_t)data.length);
}

@end
