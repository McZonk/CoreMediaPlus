#include "CMPBlockBuffer+Text.h"

#include <TargetConditionals.h>

#include "CMPAtoms.h"
#include "CMPAtoms+Iterate.h"
#include "CMPErrors.h"


typedef struct TextEncodingModifierBox
{
	uint32_t	size;
	OSType		type;
	uint32_t	encoding;
} TextEncodingModifierBox;

OSStatus CMPBlockBufferCreateWithText(CFAllocatorRef allocator, CFStringRef text, CMBlockBufferRef* outBlockBuffer)
{
	CFDataRef utfData = CFStringCreateExternalRepresentation( NULL, text, kCFStringEncodingUTF8, '?' );
	if (utfData == NULL)	// should not happen
	{
		return CMPParameterError;
	}
	CFIndex textLengthUTF8 = CFDataGetLength( utfData );
	if (textLengthUTF8 > USHRT_MAX)
	{
		// Text is too long to record the length in a uint16_t
		CFRelease( utfData );
		return CMPParameterError;
	}
	const uint8_t* textData = CFDataGetBytePtr( utfData );
	
	size_t bufferLength = sizeof(uint16_t) + textLengthUTF8 + sizeof(TextEncodingModifierBox);
	
	OSStatus status = CMBlockBufferCreateWithMemoryBlock(allocator, NULL, bufferLength, allocator, NULL, 0, bufferLength, kCMBlockBufferAssureMemoryNowFlag, outBlockBuffer);
	if (status != noErr)
	{
		CFRelease( utfData );
		return status;
	}
	
	char *buffer = NULL;
	status = CMBlockBufferGetDataPointer(*outBlockBuffer, 0, NULL, NULL, &buffer);
	if (status != noErr)
	{
		CFRelease( utfData );
		return status;
	}
	
	*(uint16_t *)buffer = CFSwapInt16HostToBig(textLengthUTF8);
	buffer += sizeof(uint16_t);
	
	memcpy(buffer, textData, textLengthUTF8);
	buffer += textLengthUTF8;
	CFRelease( utfData );
	
	// write an explicit encoding atom here!
	TextEncodingModifierBox encodingBox;
	encodingBox.size = CFSwapInt32HostToBig( sizeof(TextEncodingModifierBox) );
	encodingBox.type = CFSwapInt32HostToBig('encd');
	encodingBox.encoding = CFSwapInt32HostToBig(kCFStringEncodingUTF8);
	memcpy( buffer, &encodingBox, sizeof(encodingBox) );
	
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
