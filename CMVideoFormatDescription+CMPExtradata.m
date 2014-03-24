#include "CMVideoFormatDescription+CMPExtradata.h"

OSStatus CMPVideoFormatDescriptionCopyExtradata(CFAllocatorRef allocator, CMVideoFormatDescriptionRef formatDescription, CFDataRef *outExtradata)
{
	const FourCharCode mediaSubType = CMFormatDescriptionGetMediaSubType(formatDescription);
	if(mediaSubType == kCMVideoCodecType_MPEG4Video || mediaSubType == kCMVideoCodecType_H264)
	{
		CFDictionaryRef atoms = CMFormatDescriptionGetExtension(formatDescription, kCMFormatDescriptionExtension_SampleDescriptionExtensionAtoms);
		
		CFDataRef extradata = CFDictionaryGetValue(atoms, CFSTR("avcC"));
		if(extradata == nil)
		{
			return paramErr;
		}
		
		*outExtradata = CFDataCreateCopy(allocator, extradata);
		return noErr;
	}
	else
	{
		*outExtradata = NULL;
		return noErr;
	}
}
