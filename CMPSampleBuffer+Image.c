#include "CMPSampleBuffer+Image.h"

#include "CMPAtoms.h"
#include "CMPBlockBuffer+Image.h"


CGImageRef CMPSampleBufferCopyImage(CFAllocatorRef allocator, CMSampleBufferRef sampleBuffer)
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
	if(mediaType != kCMMediaType_Video)
	{
		return NULL;
	}

	CMBlockBufferRef blockBuffer = CMSampleBufferGetDataBuffer(sampleBuffer);
	if(blockBuffer == NULL)
	{
		return NULL;
	}

	FourCharCode mediaSubType = CMFormatDescriptionGetMediaSubType(formatDescription);

	if(mediaSubType == CMPAtomTypeJpeg)
	{
		return CMPBlockBufferCopyJPEGImage(allocator, blockBuffer);
	}
	
	if(mediaSubType == CMPAtomTypePng)
	{
		return CMPBlockBufferCopyPNGImage(allocator, blockBuffer);
	}
	
	return NULL;
}
