#include "events.h"
#include "window.h"
#include "debug.h"

// Array of registered scancodes
// Length equal to the number registered
// Elements are scancodes, which can be used in the input state array
static Uint8 * gm_registeredButtons = NULL;
static size_t gm_registeredCount = 0;

// An array of input states (bitfields)
// Indices are 0 to SDL_NUM_SCANCODES
static Uint8 * gm_inputStateArray = NULL;

int gm_initializeInputStateArray()
{
    gm_inputStateArray = calloc(SDL_NUM_SCANCODES, sizeof(Uint8));
    if (!gm_inputStateArray)
    {
        gm_setError(ERR_CODE,ERR_NOMEM);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int gm_registerScancode(int scancode)
{
    if (scancode <= 0 || scancode >= SDL_NUM_SCANCODES) return -1;
	// Extend registered LUT to house new scancode
	Uint8 * mem = realloc(gm_registeredButtons, sizeof(Uint8) * (1 + gm_registeredCount));
	if (!mem)
	{
		gm_setError(ERR_CODE, ERR_NOMEM);
		return -1;
	}
    gm_registeredButtons = mem;
    gm_registeredButtons[gm_registeredCount++] = scancode;
    return scancode;
}

void gm_destroyEventData()
{
    if (gm_inputStateArray) free(gm_inputStateArray);
    if (gm_registeredButtons) free(gm_registeredButtons);
}

int gm_buttonQuery(GLuint id, gm_ButtonQueryType_t type)
{
    if (id <= 0 || id >= SDL_NUM_SCANCODES)
    {
        gm_setError(ERR_MESG, "Couldn't query id %x (out of bounds)!\n", id);
        return -1;
    }
    Uint8 state = gm_inputStateArray[id];
    return state & type;
}

int gm_handleEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					gm_windowWidth = event.window.data1;
					gm_windowHeight = event.window.data2;
					glViewport(0,0,gm_windowWidth,gm_windowHeight);
				}
				break;
			case SDL_QUIT:
				return GM_QUIT;
			default:
				break;
		}
	}
	return EXIT_SUCCESS;
}