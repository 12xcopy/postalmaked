

enum
{
    POSTAL_GAMEMODE_unknown,
    POSTAL_GAMEMODE_TitleSequence, //the entire sequence
    POSTAL_GAMEMODE_MenuLogo, //POSTAL
    POSTAL_GAMEMODE_MenuScreens,
    POSTAL_GAMEMODE_LevelLoad, //progress bar screen
    POSTAL_GAMEMODE_LevelIntro, //aah screamy face and scary text
    POSTAL_GAMEMODE_Level, //running around having a ball
};


int pgamemode_get();
void pgamemode_set(int nu);

int pgamemode_skip_title(int v);