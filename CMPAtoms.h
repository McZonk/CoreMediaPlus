#pragma once

#include <CoreMedia/CoreMedia.h>

// kCMTextFormatType_QTText

static const FourCharCode kCMPTextEncoding = 'encd';

static const FourCharCode CMPAtomTypeEncoding = 'encd';


static const FourCharCode kCMPImageTypeJpeg = 'jpeg';
static const FourCharCode kCMPImageTypePng = 'png ';


typedef struct CMPAtom {
	UInt32 size;
	FourCharCode type;
} CMPAtom;


typedef struct CMPEncodingAtom {
	CMPAtom atom;
	UInt32 encoding;
} CMPEncodingAtom;


CFStringRef CMPAtomTypeCopyStringRef(CFAllocatorRef allocator, FourCharCode type);
