#include "CMBlockBuffer+CMPData.h"

OSStatus CMPBlockBufferAppendToData(CMBlockBufferRef blockBuffer, CFMutableDataRef data)
{
	const size_t length = CMBlockBufferGetDataLength(blockBuffer);
	
	return CMPBlockBufferAppendRangeToData(blockBuffer, 0, length, data);
}

OSStatus CMPBlockBufferAppendRangeToData(CMBlockBufferRef blockBuffer, size_t offset, size_t length, CFMutableDataRef data)
{
	do
	{
		char *dataPointer = NULL;
		size_t lengthAtOffset = 0;
		CMBlockBufferGetDataPointer(blockBuffer, offset, &lengthAtOffset, NULL, &dataPointer);
		
		if(lengthAtOffset > length)
		{
			lengthAtOffset = length;
		}
			
		offset += lengthAtOffset;
		length -= lengthAtOffset;
		
		CFDataAppendBytes(data, (UInt8 *)dataPointer, lengthAtOffset);
	}
	while(length > 0);

	return noErr;
}
