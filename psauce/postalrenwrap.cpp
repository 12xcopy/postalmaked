#include <inttypes.h>
#include "postalrenwrap.h"
#include "scene.h"
extern "C"
{
	#include "gltest.h"
}
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

class CScene* pscene;
class CCamera* pcamera;
class CHood* phood;

//hood & camera are tucked away in play.cpp but i need them for rendering.. so
void psauc_NotifyScene(class CScene* scene)
{
	pscene = scene;
}
void psauc_NotifyCamera(class CCamera* v)
{
	pcamera=v;
}
void psauc_NotifyHood(class CHood* v)
{
	phood=v;
}


int gltest_getHoodBackground(int* w,int* h,uint8_t** image,int *pitch)
{
	if (!phood) return 1;
	*w = phood->m_pimBackground->m_sWidth;
	*h = phood->m_pimBackground->m_sHeight;

	*image = phood->m_pimBackground->m_pData;
	*pitch = phood->m_pimBackground->m_lPitch;
	return 0;
}

void psauc_ResetRender()
{
	pscene=0;
	pcamera=0;
	phood=0;
	gltest_unload_scene();
}