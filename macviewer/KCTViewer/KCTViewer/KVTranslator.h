//
//  KVTranslator.h
//  KCTViewer
//
//  Created by Johannes Ekberg on 2014-01-21.
//  Copyright (c) 2014 the KanColleTool team. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KVTranslator : NSObject
@property (nonatomic, strong) NSDictionary *tldata;

+ (instancetype)sharedTranslator;

- (NSString *)translate:(NSString *)line;
- (NSData *)translateJSON:(NSData *)json;

@end
