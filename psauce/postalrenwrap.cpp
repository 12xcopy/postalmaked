#include <inttypes.h>
#include "postalrenwrap.h"

// yeah this sucks, but the raw data for the palette wants to be static
// so these functions are the only way im letting C code interact with it


void psaucSetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes)
{
	rspSetPaletteEntries(sStartIndex, sCount, pucRed, pucGreen, pucBlue, lIncBytes);
}

void psaucGetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes)
{
	rspGetPaletteEntries(sStartIndex, sCount, pucRed, pucGreen, pucBlue, lIncBytes);
}