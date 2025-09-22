#include "sauceinput.h"
#include <SDL2/SDL.h>
#include "pgamemode.h"
#include <inttypes.h>

int skipkey(int k)
{
	return k == '\r' || k == ' ' || k == 27 /* escape */;
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

		if (skipkey(e->key.keysym.sym) &&
		    (gamemode == POSTAL_GAMEMODE_TitleSequence ||
			POSTAL_GAMEMODE_LevelIntro))
		{
			// user wants to skip ahead
			pgamemode_skip_title(1);
			return 0;
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