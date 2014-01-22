#include "CMPBlockBuffer+Image.h"


CGImageRef CMPBlockBufferCopyJPEGImage(CFAllocatorRef allocator, CMBlockBufferRef blockBuffer)
{
	char *buffer = NULL;
	size_t size = 0;
	
	OSStatus status = CMBlockBufferGetDataPointer(blockBuffer, 0, &size, NULL, &buffer);
	if(status != noErr)
	{
		return NULL;
	}
	
	CGDataProviderRef source = CGDataProviderCreateWithData(NULL, buffer, size, NULL);
	
	CGImageRef image = CGImageCreateWithJPEGDataProvider(source, NULL, false, kCGRenderingIntentDefault);
	
	CFRelease(source);
	
	return image;
}

CGImageRef CMPBlockBufferCopyPNGImage(CFAllocatorRef allocator, CMBlockBufferRef blockBuffer)
{
	char *buffer = NULL;
	size_t size = 0;
	
	OSStatus status = CMBlockBufferGetDataPointer(blockBuffer, 0, &size, NULL, &buffer);
	if(status != noErr)
	{
		return NULL;
	}
	
	CGDataProviderRef source = CGDataProviderCreateWithData(NULL, buffer, size, NULL);
	
	CGImageRef image = CGImageCreateWithPNGDataProvider(source, NULL, false, kCGRenderingIntentDefault);
	
	CFRelease(source);
	
	return image;
}
