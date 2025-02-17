#include "delay.h"

float gm_fps = 60.0f;

void gm_msDelay(float ms)
{
	SDL_Delay(ms);
}

void gm_setFrameRate(float fps)
{
	gm_fps = fps;
}

Uint64 gm_msAtEndOfFrame;

void gm_beginFrame()
{
	gm_msAtEndOfFrame = SDL_GetTicks64() + (1000.0 / gm_fps);
}

void gm_endFrame()
{
	long remaining_ms = gm_msAtEndOfFrame - SDL_GetTicks64();
	if (remaining_ms <= 10) return;
	SDL_Delay(remaining_ms);
}