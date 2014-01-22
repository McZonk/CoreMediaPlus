#pragma once

#include <CoreMedia/CoreMedia.h>

static const FourCharCode CMPAtomTypeEncoding = 'encd';

static const FourCharCode CMPAtomTypeText = 'text';
static const FourCharCode CMPAtomTypeText3G = 'tx3g';

static const FourCharCode CMPAtomTypeJpeg = 'jpeg';
static const FourCharCode CMPAtomTypePng = 'png ';


typedef struct CMPAtom {
	UInt32 size;
	FourCharCode type;
} CMPAtom;


typedef struct CMPEncodingAtom {
	CMPAtom atom;
	UInt32 encoding;
} CMPEncodingAtom;


CFStringRef CMPAtomTypeCopyStringRef(CFAllocatorRef allocator, FourCharCode type);
