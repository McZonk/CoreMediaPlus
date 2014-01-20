#include "CMPBlockBuffer+Text.h"

static const UInt32 CMPTextTerminator = 0x0000000c;
static const UInt32 CMPTextEncoding = FOUR_CHAR_CODE('encd');
static const UInt32 CMPTextEncodingUTF8 = 0x00000100; // != kCFEncodingStringUTF8


OSStatus CMPBlockBufferCreateWithText(CFAllocatorRef allocator, CFStringRef text, CMBlockBufferRef* outBlockBuffer) {
	CFIndex textLength = CFStringGetLength(text);
	
	if(textLength > 65535)
	{
		return paramErr;
	}
	
	const char *textCharacters = CFStringGetCStringPtr(text, kCFStringEncodingUTF8);
	if(textCharacters == NULL)
	{
		return paramErr;
	}
	
	size_t bufferLength = 2 + textLength + 4 + 4 + 4;
	
	OSStatus status = CMBlockBufferCreateWithMemoryBlock(allocator, NULL, bufferLength, allocator, NULL, 0, bufferLength, kCMBlockBufferAssureMemoryNowFlag, outBlockBuffer);
	if(status != noErr)
	{
		return status;
	}
	
	char *buffer = NULL;
	status = CMBlockBufferGetDataPointer(*outBlockBuffer, 0, NULL, NULL, &buffer);
	if(status != noErr)
	{
		return status;
	}
	
	// text
	*(UInt16 *)buffer = OSSwapHostToBigInt16(textLength);
	buffer += 2;
	
	memcpy(buffer, textCharacters, textLength);
	buffer += textLength;
	
	*(UInt32 *)buffer = OSSwapHostToBigInt32(CMPTextTerminator);
	buffer += 4;
	
	// encoding
	*(UInt32 *)buffer = OSSwapHostToBigInt32(CMPTextEncoding);
	buffer += 4;
	
	*(UInt32 *)buffer = OSSwapHostToBigInt32(CMPTextEncodingUTF8);
	buffer += 4;
	
	return noErr;
}

CFStringRef CMPBlockBufferCopyText(CFAllocatorRef allocator, CMBlockBufferRef blockBuffer)
{
	char *buffer = NULL;
	size_t size = 0;
	
	OSStatus status = CMBlockBufferGetDataPointer(blockBuffer, 0, &size, NULL, &buffer);
	if(status != noErr)
	{
		return NULL;
	}
	
	// check if we can read the size
	if(size < 2)
	{
		return NULL;
	}
	
	CFIndex textLength = OSSwapBigToHostInt16(*(UInt16 *)buffer);
	buffer += 2;
	
	// check if the size is big enough for all values
	if(size < 2 + textLength + 4 + 4 + 4)
	{
		return NULL;
	}
	
	const UInt8 *textCharacters = (UInt8 *)buffer;
	buffer += textLength;
	
	UInt32 terminator = OSSwapBigToHostInt32(*(UInt32 *)buffer);
	buffer += 4;
	if(terminator != CMPTextTerminator)
	{
		return NULL;
	}
	
	UInt32 encoding = OSSwapBigToHostInt32(*(UInt32 *)buffer);
	buffer += 4;
	if(encoding != CMPTextEncoding)
	{
		return NULL;
	}
	
	// TODO: support different encodings
	UInt32 encodingUTF8 = OSSwapBigToHostInt32(*(UInt32 *)buffer);
	buffer += 4;
	if(encodingUTF8 != CMPTextEncodingUTF8)
	{
		return NULL;
	}
	
	return CFStringCreateWithBytes(allocator, textCharacters, textLength, kCFStringEncodingUTF8, false);
}
