#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "color.h"
#include "debug.h"

extern SDL_Window *gm_window;
extern SDL_GLContext *gm_glContext;
extern int gm_windowWidth;
extern int gm_windowHeight;
#define GM_ASPECTRATIO (gm_windowWidth / (float)gm_windowHeight)

/**
 * Initializes the GM and opens a window.
 * The inverse of this is `gm_exit()`
 *
 * @param winTitle Title to give the initial window
 * @param win_x initial x position of the window
 * @param win_y initial y position of the window
 * @param win_w initial width of the window
 * @param win_h initial height of the window
 * @param min_win_w initial minimum width of the window
 * @param min_win_h initial minimum height of the window
 *
 * @return `EXIT_SUCCESS` (`0`) if everything initialized as expected. Otherwise, you will have to check the error with `whatHappened()`
 */
NODISCARD
int gm_initWindow(const char * winTitle,
				Uint32 win_x, Uint32 win_y, Uint32 win_w, Uint32 win_h, Uint32 min_win_w, Uint32 min_win_h);

void gm_renderClear(gm_Color_t clearColor);
void gm_renderDisplay();

void gm_setWireframe(bool wireframe);

/**
 * Closes the window and releases any GM memory
 *
 */
void gm_exit();

#endif