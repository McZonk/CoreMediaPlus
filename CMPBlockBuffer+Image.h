#pragma once

#include <CoreMedia/CoreMedia.h>
#include <CoreGraphics/CoreGraphics.h>


CGImageRef CMPBlockBufferCopyJPEGImage(CFAllocatorRef allocator, CMBlockBufferRef blockBuffer);

CGImageRef CMPBlockBufferCopyPNGImage(CFAllocatorRef allocator, CMBlockBufferRef blockBuffer);
