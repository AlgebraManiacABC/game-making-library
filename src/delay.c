#include <SDL2/SDL.h>
#include "delay.h"

static float gm_fps = 60.0f;

void gm_msDelay(Uint32 ms)
{
	SDL_Delay(ms);
}

void gm_setFrameRate(float fps)
{
	gm_fps = fps;
}

float gm_getFrameRate()
{
	return gm_fps;
}

static Uint64 gm_expectedEndOfFrame;
float deltaTime = 1 / 60.0f;

void gm_beginFrame()
{
	gm_expectedEndOfFrame = (Uint64)(SDL_GetTicks64() + (1000.0f / gm_fps));
}

void gm_endFrame()
{
	Uint64 now = SDL_GetTicks64();
	if (now + 10 > gm_expectedEndOfFrame)
	{
		deltaTime += ((long)((now+10) - gm_expectedEndOfFrame) - 10) / 1000.0f;
		return;
	}

	Uint32 remaining_ms = (Uint32)(gm_expectedEndOfFrame - now);
	SDL_Delay(remaining_ms);
	deltaTime = 1.0f / gm_fps;
}