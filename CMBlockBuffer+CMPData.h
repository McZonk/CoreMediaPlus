#include <CoreMedia/CoreMedia.h>

OSStatus CMPBlockBufferAppendToData(CMBlockBufferRef blockBuffer, CFMutableDataRef data);

OSStatus CMPBlockBufferAppendRangeToData(CMBlockBufferRef blockBuffer, size_t offset, size_t length, CFMutableDataRef data);
