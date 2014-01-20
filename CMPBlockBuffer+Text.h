#pragma once

#include <CoreMedia/CoreMedia.h>

OSStatus CMPBlockBufferCreateWithText(CFAllocatorRef allocator, CFStringRef text, CMBlockBufferRef* outBlockBuffer);

CFStringRef CMPBlockBufferCopyText(CFAllocatorRef allocator, CMBlockBufferRef blockBuffer);
