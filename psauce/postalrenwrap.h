#include <inttypes.h>

/* C / C++ header file */

/* Use these instead of postal/RSPiX if you're using C */

#ifdef __cplusplus
extern "C" {
#endif

void psaucSetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);

 void psaucGetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);

#ifdef __cplusplus
 }

// these functions are defined in Bdisp.cpp in BLUE
extern void rspSetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);

extern void rspGetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);


#endif