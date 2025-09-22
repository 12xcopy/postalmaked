#include <inttypes.h>
union SDL_Event;
int psauce_inputevent(union SDL_Event* e);

// not yet
#define PSAUCE_USE_OWN_INPUTEVENTS 0

#if PSAUCE_USE_OWN_INPUTEVENTS == 0
#undef PSAUCE_USE_OWN_INPUTEVENTS
#endif

struct RInputEvent;
int16_t psaucGetNextInputEvent(struct RInputEvent *pie);

void psaucClearKeyInputEvents(void);
void psaucClearMouseInputEvents(void);
void psaucClearAllInputEvents(void);