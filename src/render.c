#include "render.h"
#include "window.h"

void gm_renderDisplay()
{
	SDL_GL_SwapWindow(gm_window);
}

void gm_renderClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}