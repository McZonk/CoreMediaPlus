#pragma once

#include <CoreMedia/CoreMedia.h>

OSStatus CMPSampleBufferCreateWithText(CFAllocatorRef allocator, CFStringRef text, Boolean dataReady, CMSampleBufferMakeDataReadyCallback makeDataReadyCallback, void *makeDataReadyRefcon, CMFormatDescriptionRef formatDescription, const CMSampleTimingInfo *sampleTiming, CMSampleBufferRef *outSampleBuffer);

CFStringRef CMPSampleBufferCopyText(CFAllocatorRef allocator, CMSampleBufferRef sampleBuffer);
