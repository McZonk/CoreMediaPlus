#pragma once

#include <CoreMedia/CoreMedia.h>

OSStatus CMP3GTextFormatDescriptionCreate(CFAllocatorRef allocator, CMFormatDescriptionRef *outFormatDescription);

OSStatus CMPTextFormatDescriptionCreate(CFAllocatorRef allocator, CMTextFormatType subtype, CMFormatDescriptionRef *outFormatDescription);
