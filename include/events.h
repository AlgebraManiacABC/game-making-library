#ifndef EVENTS_H
#define EVENTS_H

#include <stdbool.h>
#include <SDL2/SDL_types.h>
#include "debug.h"

#define GM_QUIT (1)

extern Uint64 gm_heldKeys;
extern Uint64 gm_releasedKeys;

extern Uint32 gm_mouseState;

NODISCARD
/**
 * Reads any current events, and handles them.
 * Any user-registered functions will be called if their respective event occurs.
 *
 * @returns 0 on success, 1 if SDL_QUIT called (remaining queued events are ignored this call), or -1 if error
 */
int gm_handleEvents();

#endif