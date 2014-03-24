#include "CMAudioFormatDescription+CMPExtradata.h"

#include <TargetConditionals.h>
#if defined(TARGET_OS_IPHONE) && (TARGET_OS_IPHONE > 0)
#include <MacErrors.h>
#endif


static OSStatus AudioDataGetTag(const uint8_t *data, uint32_t dataLength, uint8_t *outTagType, uint32_t *outTagHeaderLength, uint32_t *outTagDataLength)
{
	static const uint8_t lengthMask = 0x7f;
	static const uint8_t endMask = ~lengthMask;

	if(dataLength < 1)
	{
		return paramErr;
	}

	uint8_t type = data[0];
	
	uint32_t length = 0;
	uint32_t index = 1;
	
	for(; index <= 4; ++index)
	{
		if(dataLength < index + 1)
		{
			return paramErr;
		}
		
		const uint8_t b = data[index];
		
		length = (length << 7) | (b & lengthMask);
		
		if(!(b & endMask))
		{
			break;
		}
	}
	
	if(outTagType != NULL)
	{
		*outTagType = type;
	}
	
	if(outTagHeaderLength != NULL)
	{
		*outTagHeaderLength = 1 + index;
	}
	
	if(outTagDataLength != NULL)
	{
		*outTagDataLength = length;
	}
	
	return noErr;
}

static OSStatus AudioDataCopyExtradata(CFAllocatorRef allocator, const uint8_t *data, uint32_t dataSize, CFDataRef *outExtradata)
{
	static const uint8_t ESDSTag = 0x03;
	static const uint8_t ESDSConfigTag = 0x04;
	static const uint8_t ESDSSpecifcTag = 0x05;
	
	uint8_t tag = 0;
	uint32_t tagDataLength = 0;
	uint32_t tagHeaderLength = 0;
	
	OSStatus status = AudioDataGetTag(data, dataSize, &tag, &tagHeaderLength, &tagDataLength);
	if(status != noErr)
	{
		return status;
	}
	
	data += tagHeaderLength;
	dataSize -= tagHeaderLength;
	
	const uint32_t skipSize = tag == ESDSTag ? 3 : 2;
	
	if(dataSize < skipSize)
	{
		return paramErr;
	}
	data += skipSize;
	dataSize -= skipSize;
	
	status = AudioDataGetTag(data, dataSize, &tag, &tagHeaderLength, &tagDataLength);
	if(status != noErr)
	{
		return status;
	}

	data += tagHeaderLength;
	dataSize -= tagHeaderLength;

	if(tag == ESDSConfigTag)
	{
		const uint32_t configSize = 13;
		
		if(dataSize < configSize)
		{
			return paramErr;
		}
		data += configSize;
		dataSize -= configSize;
		
		status = AudioDataGetTag(data, dataSize, &tag, &tagHeaderLength, &tagDataLength);
		if(status != noErr)
		{
			return status;
		}
		
		data += tagHeaderLength;
		dataSize -= tagHeaderLength;
		
		if(dataSize < tagDataLength)
		{
			return paramErr;
		}
		
		if(tag == ESDSSpecifcTag)
		{
			*outExtradata = CFDataCreate(allocator, data, tagDataLength);
			return noErr;
		}
	}
	
	return paramErr;
}

OSStatus CMPAudioFormatDescriptionCopyExtradata(CFAllocatorRef allocator, CMAudioFormatDescriptionRef formatDescription, CFDataRef* outExtradata)
{
	if(formatDescription == NULL)
	{
		return paramErr;
	}
	
	const FourCharCode mediaSubType = CMFormatDescriptionGetMediaSubType(formatDescription);
	if(mediaSubType == kAudioFormatMPEG4AAC)
	{
		size_t magicCookieSize = 0;
		const unsigned char *magicCookie = CMAudioFormatDescriptionGetMagicCookie(formatDescription, &magicCookieSize);
		
		if(magicCookie == NULL || magicCookieSize == 0)
		{
			return paramErr;
		}
		
		return AudioDataCopyExtradata(allocator, magicCookie, (uint32_t)magicCookieSize, outExtradata);
	}
	else
	{
		*outExtradata = NULL;
		return noErr;
	}
}
