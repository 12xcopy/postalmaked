#include "pgamemode.h"
#include <stdio.h>

int GPGamemode = 0;


int pgamemode_get() {return GPGamemode;}


static const char* gamemodenames[] =
{
    "POSTAL_GAMEMODE_unknown",
    "POSTAL_GAMEMODE_TitleSequence", //the entire sequence
    "POSTAL_GAMEMODE_MenuLogo", //POSTAL
    "POSTAL_GAMEMODE_MenuScreens",
    "POSTAL_GAMEMODE_LevelLoad", //progress bar screen
    "POSTAL_GAMEMODE_LevelIntro", //aah screamy face and scary text
    "POSTAL_GAMEMODE_Level", //running around having a ball
};


void pgamemode_set(int nu) {
	if (nu != GPGamemode)
		printf("pgamemode is NOW %i (%s)\n",nu,gamemodenames[nu]);
	GPGamemode = nu;
}


int skip_title=0;
//also applies for loading screens and transitions
int pgamemode_skip_title(int v)
{
    int ov = skip_title;
    if (v != skip_title)
    {
        skip_title = v;
    }
    return ov;
}