#include "CMPBlockBuffer+Text.h"
#include "CMPAtoms.h"
#include "CMPAtoms+Iterate.h"


OSStatus CMPBlockBufferCreateWithText(CFAllocatorRef allocator, CFStringRef text, CMBlockBufferRef* outBlockBuffer) {
	CFIndex textLengthUTF16 = CFStringGetLength(text);
	if(textLengthUTF16 > USHRT_MAX)
	{
		// text is too long in utf16
		return paramErr;
	}

	const char *textCharacters = CFStringGetCStringPtr(text, kCFStringEncodingUTF8);
	Boolean textCharactersNeedsFree = false;
	CFIndex textLengthUTF8 = textLengthUTF16;
	
	if(textCharacters == NULL)
	{
		// if there are umlauts or other special characters CFStringGetCStringPtr returns NULL
		
		CFRange range = CFRangeMake(0, textLengthUTF16);
		
		CFIndex length = CFStringGetBytes(text, range, kCFStringEncodingUTF8, 0, false, NULL, 0, &textLengthUTF8);
		if(length != textLengthUTF16)
		{
			// unable to encode the string
			return paramErr;
		}
		
		if(textLengthUTF8 > USHRT_MAX)
		{
			// text is too long in utf8
			return paramErr;
		}
		
		// allocate one byte more than needed to append \0 for debugging
		textCharacters = calloc(textLengthUTF8 + 1, 1);
		textCharactersNeedsFree = true;

		length = CFStringGetBytes(text, CFRangeMake(0, textLengthUTF16), kCFStringEncodingUTF8, 0, false, (UInt8 *)textCharacters, textLengthUTF8 + 1, &textLengthUTF8);
		if(length != textLengthUTF16)
		{
			// unable to encode the string, this should never happen
			free((void *)textCharacters);
			return paramErr;
		}
	}
	
	size_t bufferLength = 2 + textLengthUTF8;
	
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
	
	*(uint16_t *)buffer = OSSwapHostToBigInt16(textLengthUTF8);
	buffer += sizeof(uint16_t);
	
	memcpy(buffer, textCharacters, textLengthUTF8);
	buffer += textLengthUTF8;
	
	// TODO: write an explicit encoding atom here?
	
	if(textCharactersNeedsFree)
	{
		free((void *)textCharacters);
	}
	
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
	size -= 2;
	
	// check if the size is big enough for all values
	if(size < textLength)
	{
		return NULL;
	}
		
	const UInt8 *textCharacters = (UInt8 *)buffer;
	buffer += textLength;
	size -= textLength;
		
	CFStringEncoding textEncoding = kCFStringEncodingUTF8;
	
	// read appended atoms
	if(size > 0)
	{
		size_t offset = 0;
		CMPAtom *atom = NULL;
	
		while(CMPAtomIterate(buffer, size, &offset, &atom))
		{
			FourCharCode atomType = OSSwapBigToHostInt32(atom->type);
			UInt32 atomSize = OSSwapBigToHostInt32(atom->size);
			
			if(atomType == CMPAtomTypeEncoding)
			{
				CMPEncodingAtom *encodingAtom = (CMPEncodingAtom *)atom;
				
				// atom does not fit
				if(atomSize > sizeof(*encodingAtom))
				{
					continue;
				}
				
				textEncoding = OSSwapBigToHostInt32(encodingAtom->encoding);
			}
		}
	}
	
	// search "User Data Text Strings and Language Codes"
	// https://developer.apple.com/library/mac/documentation/QuickTime/qtff/QTFFChap2/qtff2.html#//apple_ref/doc/uid/TP40000939-CH204-BBCCFFGD

	if(textLength > 2)
	{
		UInt16 bom = *(UInt16 *)textCharacters;
		if(textEncoding == kCFStringEncodingUTF8)
		{
			if(bom == 0xfeff || bom == 0xfffe)
			{
				textEncoding = kCFStringEncodingUTF16;
			}
		}
		else if(textEncoding == kCFStringEncodingUTF16)
		{
			if(bom != 0xfeff && bom != 0xfffe)
			{
				textEncoding = kCFStringEncodingUTF8;
			}
		}
	}
	
	return CFStringCreateWithBytes(allocator, textCharacters, textLength, textEncoding, false);
}
