#ifndef EVENTS_H
#define EVENTS_H

#include "debug.h"

#define GM_QUIT (1)

extern Uint32 gm_mouseState;

/**
 * Registers the given scancode with llgml for watching.
 * Can query state with `gm_buttonQuery`
 *
 * @param scancode the SDL_Scancode to track
 * @return a unique identifier for the scancode in llgml. Will be negative on fail.
 */
int gm_registerScancode(int scancode);

typedef enum gm_ButtonQueryType_e
{
    BUTTON_QUERY_HELD = 0b001,
    BUTTON_QUERY_JUST_PRESSED = 0b010,
    BUTTON_QUERY_JUST_RELEASED = 0b100,
    // TODO: timed repeat

}   gm_ButtonQueryType_t;

/**
 * Checks and returns the specific state of the given button key
 *
 * @param id the id of the button to query
 * @param type how the button should be queried (`gm_ButtonQueryType_t`)
 * @return the current button state of that query type
 */
int gm_buttonQuery(GLuint id, gm_ButtonQueryType_t type);

/**
 * Reads any current events, and handles them.
 * Any user-registered functions will be called if their respective event occurs.
 *
 * @returns 0 on success, 1 if SDL_QUIT called (remaining queued events are ignored this call), or -1 if error
 */
NODISCARD
int gm_handleEvents();

#endif