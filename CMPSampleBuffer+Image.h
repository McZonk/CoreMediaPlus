#pragma once

#include <CoreMedia/CoreMedia.h>
#include <CoreGraphics/CoreGraphics.h>


CGImageRef CMPSampleBufferCopyImage(CFAllocatorRef allocator, CMSampleBufferRef sampleBuffer);
