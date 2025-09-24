

enum
{
    POSTAL_GAMEMODE_unknown,
    POSTAL_GAMEMODE_TitleSequence, //the entire sequence
    POSTAL_GAMEMODE_MenuLogo, //POSTAL
    POSTAL_GAMEMODE_MenuScreens,
    POSTAL_GAMEMODE_LevelCutscene_Loading, //progress bar screen
    POSTAL_GAMEMODE_LevelCutscene,
    POSTAL_GAMEMODE_Level,
};


int pgamemode_get();
void pgamemode_set(int nu);

int pgamemode_skip_title(int v);
int pgamemode_skip_cutscene(int v);
int pgamemode_skip_demo(int v);

#include "pgm_cutscene.h"
#include "pgm_level.h"

union pgm_u
{
	struct pgm_cutscene_s LevelCutscene;
	struct pgm_level_s Level;
};
union pgm_u* pgamemode_getdata();