//
//  KCTViewerTests.m
//  KCTViewerTests
//
//  Created by Johannes Ekberg on 2013-12-27.
//  Copyright (c) 2013 the KanColleTool team. All rights reserved.
//

#import <XCTest/XCTest.h>

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

@end
