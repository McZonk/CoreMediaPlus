#include "CMPAtoms.h"

#include <string.h>

CFStringRef CMPAtomTypeCopyStringRef(CFAllocatorRef allocator, FourCharCode type)
{
	type = OSSwapBigToHostInt32(type);
	const UInt8 *characters = (UInt8 *)&type;
	
	if(isprint(characters[0]) && isprint(characters[1]) && isprint(characters[2]) && isprint(characters[3]))
	{
		return CFStringCreateWithBytes(allocator, characters, 4, kCFStringEncodingASCII, false);
	}
	else
	{
		return CFStringCreateWithFormat(allocator, NULL, CFSTR("%08x"), type);
	}
}
