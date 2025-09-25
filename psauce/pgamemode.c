#include "pgamemode.h"
#include <stdio.h>
#include <string.h>

int GPGamemode = 0;

int pgamemode_get()
{
	return GPGamemode;
}

union pgm_u PGM;

static const char *gamemodenames[] = {
    "POSTAL_GAMEMODE_unknown",
    "POSTAL_GAMEMODE_TitleSequence",
    "POSTAL_GAMEMODE_MenuLogo",
    "POSTAL_GAMEMODE_MenuScreens",
    "POSTAL_GAMEMODE_LevelCutscene_Loading",
    "POSTAL_GAMEMODE_LevelCutscene",
    "POSTAL_GAMEMODE_Level",
    "POSTAL_GAMEMODE_LevelScreens",
};

void pgamemode_set(int nu)
{
	if (nu != GPGamemode)
	{
		printf("pgamemode is NOW %i (%s)\n", nu, gamemodenames[nu]);
		memset(&PGM, 0, sizeof(PGM));
	}
	GPGamemode = nu;
}


#define skiptemplate(t) int t(int v)\
{\
	static int val;\
	int ov = val;\
	if (v != val)\
		val = v;\
	return ov;\
} 


skiptemplate(pgamemode_skip_title)
skiptemplate(pgamemode_skip_cutscene)
skiptemplate(pgamemode_skip_demo)

union pgm_u *pgamemode_getdata()
{
	return &PGM;
}