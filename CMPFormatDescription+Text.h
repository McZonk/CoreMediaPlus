#pragma once

#include <CoreMedia/CoreMedia.h>

CFDictionaryRef CMPTextFormatExtensionsDictionaryCreate(CFAllocatorRef allocator);


OSStatus CMP3GTextFormatDescriptionCreate(CFAllocatorRef allocator, CMFormatDescriptionRef *outFormatDescription);

OSStatus CMPQTTextFormatDescriptionCreate(CFAllocatorRef allocator, CMFormatDescriptionRef *outFormatDescription);

OSStatus CMPTextFormatDescriptionCreate(CFAllocatorRef allocator, CMTextFormatType subtype, CMFormatDescriptionRef *outFormatDescription);
