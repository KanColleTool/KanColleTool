//
//  NSString+KVHashes.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-21.
//  Copyright (c) 2014 the KanColleTool team. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (KVHashes)

- (NSString *)sha1;
- (NSString *)sha256;
- (unsigned long)crc32;

@end
