#ifndef DELAY_H
#define DELAY_H

#include <SDL2/SDL.h>

void gm_msDelay(float);

// Framerate functions.
// Do note: These currently work for "Maximum" framerates.
// They implement SDL_Delay, which is inherently flawed (as are most FPS-limiters).
void gm_setFrameRate(float);
void gm_beginFrame();
void gm_endFrame();

#endif