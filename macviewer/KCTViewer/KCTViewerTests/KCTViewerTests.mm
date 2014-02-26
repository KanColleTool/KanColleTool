//
//  KCTViewerTests.m
//  KCTViewerTests
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 the KanColleTool team. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "KVTranslator.h"

@interface KCTViewerTests : XCTestCase

@end

@implementation KCTViewerTests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testVersionComparison
{
	XCTAssertEqual(NSOrderedAscending, [@"0.8.1" compare:@"0.8.2" options:NSNumericSearch], @"0.8.1 >= 0.8.2");
	XCTAssertEqual(NSOrderedSame, [@"0.8.2" compare:@"0.8.2" options:NSNumericSearch], @"0.8.2 != 0.8.2");
	XCTAssertEqual(NSOrderedDescending, [@"0.8.3" compare:@"0.8.2" options:NSNumericSearch], @"0.8.3 <= 0.8.2");
}

- (void)testTranslation
{
	// Local translator instance - not a shared one, the last thing I need right now is singeltons
	KVTranslator *translator = [[KVTranslator alloc] init];
	
	// Set up some test data - 那珂 (Naka) has a translation, まるゆ (Maruyu) doesn't
	translator.tldata = @{ @"124853853": @"Naka", @"3440185848": [NSNull null] };
	
	// Try translating a translated string (Naka/那珂)
	XCTAssertEqualObjects([translator translate:@"那珂"], @"Naka", @"那珂 doesn't translate to Naka!");
	XCTAssertEqualObjects([translator translate:@"\\u90A3\\u73C2"], @"Naka", @"那珂 (escaped) doesn't translate to Naka!");
	
	// Try translating an unknown string (tesuto/テスト)
	XCTAssertEqualObjects([translator translate:@"テスト"], @"テスト", @"Unknown strings aren't untouched!");
	XCTAssertEqualObjects([translator translate:@"\\u30C6\\u30B9\\u30C8"], @"\\u30C6\\u30B9\\u30C8", @"Unknown Escaped strings aren't untouched!");
	
	// Try translating an untranslated string (Maruyu/まるゆ)
	XCTAssertEqualObjects([translator translate:@"まるゆ"], @"まるゆ", @"Untranslated strings aren't untouched!");
	XCTAssertEqualObjects([translator translate:@"\\u307E\\u308B\\u3086"], @"\\u307E\\u308B\\u3086", @"Untranslated Escaped strings aren't untouched!");
}

@end
