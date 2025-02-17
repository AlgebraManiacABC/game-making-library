#include "events.h"
#include "window.h"
#include "debug.h"

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
}