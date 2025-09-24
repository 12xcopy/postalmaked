#include "sauceinput.h"
#include <SDL2/SDL.h>
#include "pgamemode.h"
#include <inttypes.h>

int skipkey(int k)
{
	return k == '\r' || k == ' ' || k == 27 /* escape */;
}
int skipkey_demo(int k)
{
	return k == '\r' || k == 27;
}

// returns 1 if the event should be intercepted
int psauce_inputevent(union SDL_Event *e)
{
	int type = e->type;
	if (type == SDL_KEYDOWN)
	{
		if (e->key.repeat)
			return 0;

		int gamemode = pgamemode_get();
		int key	     = e->key.keysym.sym;

		if (skipkey(key))
		{
			if (gamemode == POSTAL_GAMEMODE_TitleSequence)
			{
				pgamemode_skip_title(1);
				return 0;
			}
			if (gamemode == POSTAL_GAMEMODE_LevelCutscene)
			{
				pgamemode_skip_cutscene(1);
				return 0;
			}
		}
		if (skipkey_demo(key))
		{
			if (gamemode == POSTAL_GAMEMODE_Level)
			{
				int is_demo = pgamemode_getdata()->Level.is_demo;
				if (is_demo)
					pgamemode_skip_demo(1);
			}
		}
	}
	return 0;
}

struct RInputEvent;
int16_t psaucGetNextInputEvent(struct RInputEvent *pie)
{
	return 0;
}

void psaucClearKeyInputEvents(void) {}
void psaucClearMouseInputEvents(void) {}
void psaucClearAllInputEvents(void) {}