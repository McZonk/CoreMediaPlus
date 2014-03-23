#pragma once

#include <CoreMedia/CoreMedia.h>

OSStatus CMPAudioFormatDescriptionCopyExtradata(CFAllocatorRef allocator, CMAudioFormatDescriptionRef audioFormatDescription, CFDataRef *outExtradata);
