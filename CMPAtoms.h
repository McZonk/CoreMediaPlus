#pragma once

#include <CoreMedia/CoreMedia.h>

static const FourCharCode CMPAtomTypeEncoding = 'encd';

typedef struct CMPAtom {
	UInt32 size;
	FourCharCode type;
} CMPAtom;


typedef struct CMPEncodingAtom {
	CMPAtom atom;
	UInt32 encoding;
} CMPEncodingAtom;


CFStringRef CMPAtomTypeCopyStringRef(CFAllocatorRef allocator, FourCharCode type);
