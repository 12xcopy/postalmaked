#include <inttypes.h>

/* C / C++ header file */

/* Use these instead of postal/RSPiX if you're using C */

#ifdef __cplusplus
extern "C" {
#endif
// below are C functions

void psaucSetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);

 void psaucGetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);

int gltest_getHoodBackground(int* w,int* h,uint8_t** image,int* pitch);

void psauc_ResetRender();

// END C FUNCS
// below are C++ functions
#ifdef __cplusplus
 }

// these functions are defined in Bdisp.cpp in BLUE
extern void rspSetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);

extern void rspGetPaletteEntries(int16_t sStartIndex, int16_t sCount, uint8_t *pucRed,
    uint8_t *pucGreen, uint8_t *pucBlue, int32_t lIncBytes);



void psauc_NotifyScene(class CScene* scene);
void psauc_NotifyCamera(class CCamera* v);
void psauc_NotifyHood(class CHood* v);


//END C++ FUNCS
#endif