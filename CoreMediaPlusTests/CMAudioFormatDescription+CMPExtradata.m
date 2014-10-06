//
//  CoreMediaPlusTests.m
//  CoreMediaPlusTests
//
//  Created by Maximilian Christ on 06/10/14.
//  Copyright (c) 2014 McZonk. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import <AVFoundation/AVFoundation.h>

#import "CMAudioFormatDescription+CMPExtradata.h"


@interface CMAudioFormatDescription_CMPExtradata : XCTestCase

@end

@implementation CMAudioFormatDescription_CMPExtradata

- (void)setUp
{
	[super setUp];
}

- (void)tearDown
{
	[super tearDown];
}

- (void)testM4A
{
	NSBundle *bundle = [NSBundle bundleForClass:self.class];
	XCTAssert(bundle != nil);
	
	NSURL *URL = [bundle URLForResource:@"Baby" withExtension:@"m4a"];
	XCTAssert(URL != nil);
	
	AVAsset *asset = [AVAsset assetWithURL:URL];
	XCTAssert(asset != nil);
	
	AVAssetTrack *track = [asset tracksWithMediaType:AVMediaTypeAudio].firstObject;
	XCTAssert(track != nil);
	
	CMAudioFormatDescriptionRef formatDescription = (__bridge CMFormatDescriptionRef)track.formatDescriptions.firstObject;
	XCTAssert(formatDescription != nil);
	
	CFDataRef cfdata = NULL;
	OSStatus status = CMPAudioFormatDescriptionCopyExtradata(NULL, formatDescription, &cfdata);
	NSData *actualData = CFBridgingRelease(cfdata);
	
	XCTAssert(status == noErr);
	XCTAssert(actualData != nil);
	
	const uint8_t expectedBytes[] = { 0x11, 0x90 };
	NSData *expectedData = [NSData dataWithBytes:expectedBytes length:sizeof(expectedBytes)];
	
	XCTAssertEqualObjects(actualData, expectedData);
}

- (void)testWAV
{
	NSBundle *bundle = [NSBundle bundleForClass:self.class];
	XCTAssert(bundle != nil);
	
	NSURL *URL = [bundle URLForResource:@"Baby" withExtension:@"wav"];
	XCTAssert(URL != nil);
	
	AVAsset *asset = [AVAsset assetWithURL:URL];
	XCTAssert(asset != nil);
	
	AVAssetTrack *track = [asset tracksWithMediaType:AVMediaTypeAudio].firstObject;
	XCTAssert(track != nil);
	
	CMAudioFormatDescriptionRef formatDescription = (__bridge CMFormatDescriptionRef)track.formatDescriptions.firstObject;
	XCTAssert(formatDescription != nil);
	
	CFDataRef cfdata = NULL;
	OSStatus status = CMPAudioFormatDescriptionCopyExtradata(NULL, formatDescription, &cfdata);
	NSData *actualData = CFBridgingRelease(cfdata);
	
	XCTAssert(status == noErr);
	XCTAssert(actualData == nil); // wav doesn't have extra data
}

@end
