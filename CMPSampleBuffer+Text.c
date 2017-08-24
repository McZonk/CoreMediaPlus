#include "CMPSampleBuffer+Text.h"

#include <TargetConditionals.h>

#include "CMPAtoms.h"
#include "CMPBlockBuffer+Text.h"
#include "CMPErrors.h"


OSStatus CMPSampleBufferCreateWithText(CFAllocatorRef allocator, CFStringRef text, Boolean dataReady, CMSampleBufferMakeDataReadyCallback makeDataReadyCallback, void *makeDataReadyRefcon, CMFormatDescriptionRef formatDescription, const CMSampleTimingInfo *sampleTiming, CMSampleBufferRef *outSampleBuffer)
{
	if(text == NULL)
	{
		return CMPParameterError;
	}
	
	CMBlockBufferRef blockBuffer = NULL;
	OSStatus status = CMPBlockBufferCreateWithText(allocator, text, &blockBuffer);
	if(status != noErr)
	{
		return status;
	}
	
	size_t blockBufferLength = CMBlockBufferGetDataLength(blockBuffer);
	
	status = CMSampleBufferCreate(allocator, blockBuffer, dataReady, makeDataReadyCallback, makeDataReadyRefcon, formatDescription, 1, 1, sampleTiming, 1, &blockBufferLength, outSampleBuffer );

	CFRelease( blockBuffer );
	return status;
}

CFStringRef CMPSampleBufferCopyText(CFAllocatorRef allocator, CMSampleBufferRef sampleBuffer)
{
	if(sampleBuffer == NULL)
	{
		return NULL;
	}
	
	CMFormatDescriptionRef formatDescription = CMSampleBufferGetFormatDescription(sampleBuffer);
	if(formatDescription == NULL)
	{
		return NULL;
	}
	
	CMMediaType mediaType = CMFormatDescriptionGetMediaType(formatDescription);
	if(mediaType != kCMMediaType_Text)
	{
		return NULL;
	}
	
	FourCharCode mediaSubType = CMFormatDescriptionGetMediaSubType(formatDescription);
	if(mediaSubType != kCMTextFormatType_QTText && mediaSubType != kCMTextFormatType_3GText)
	{
		return NULL;
	}
	
	CMBlockBufferRef blockBuffer = CMSampleBufferGetDataBuffer(sampleBuffer);
	if(blockBuffer == NULL)
	{
		return NULL;
	}
	
	return CMPBlockBufferCopyText(allocator, blockBuffer);
}
