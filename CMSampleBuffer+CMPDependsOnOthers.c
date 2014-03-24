#include "CMSampleBuffer+CMPDependsOnOthers.h"

Boolean CMPSampleBufferDependsOnOthers(CMSampleBufferRef sampleBuffer)
{
	Boolean dependsOnOthers = false;
	
	CFArrayRef sampleAttachements = CMSampleBufferGetSampleAttachmentsArray(sampleBuffer, false);
	if(sampleAttachements != nil && CFArrayGetCount(sampleAttachements) > 0)
	{
		CFDictionaryRef sampleAttachment = CFArrayGetValueAtIndex(sampleAttachements, 0);
		
		CFBooleanRef dependsOnOthersNumber = CFDictionaryGetValue(sampleAttachment, kCMSampleAttachmentKey_DependsOnOthers);
		
		dependsOnOthers = CFBooleanGetValue(dependsOnOthersNumber);
	}
	
	return dependsOnOthers;
}

Boolean CMPSampleBufferIsKeyframe(CMSampleBufferRef sampleBuffer)
{
	return !CMPSampleBufferDependsOnOthers(sampleBuffer);
}
