#include "CMPAtoms+Iterate.h"

Boolean CMPAtomIterate(const void *buffer, const size_t bufferSize, size_t *ioOffset, CMPAtom **outAtom)
{
	// check if the atom header fits
	if(*ioOffset + sizeof(**outAtom) > bufferSize)
	{
		return false;
	}
	
	CMPAtom *atom = (CMPAtom *)(buffer + *ioOffset);
	
	// check if the whole atom fits
	UInt32 atomSize = OSSwapBigToHostInt32(atom->size);
	if(*ioOffset + atomSize > bufferSize)
	{
		return false;
	}
	
	*ioOffset += atomSize;
	*outAtom = atom;
	
	return true;
}
