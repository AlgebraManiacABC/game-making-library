#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "color.h"

void gm_renderClear(gm_Color clearColor);
void gm_renderDisplay();

#endif