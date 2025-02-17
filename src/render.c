#include "render.h"
#include "window.h"

void gm_renderDisplay()
{
	SDL_GL_SwapWindow(gm_window);
}

void gm_renderClear(gm_Color color)
{
	static gm_Color clearColor = GM_COLOR_BLACK;
	if (gm_ColorEquals(clearColor,color))
	{
		clearColor = color;
		glClearColor(color.r, color.g, color.b, color.a);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}