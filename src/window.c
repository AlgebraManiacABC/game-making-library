#if defined(_MSC_VER) && !defined(__clang__)
	#pragma warning(push)
	#pragma warning(disable: 4244 4018 4267) /* typical stb warnings */
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "internal/stb_image.h"
#if defined(_MSC_VER) && !defined(__clang__)
	#pragma warning(pop)
#endif
#include "window.h"
#include "internal/object_3d.h"

SDL_Window *gm_window;
SDL_GLContext *gm_glContext;
int gm_windowWidth;
int gm_windowHeight;

//	What functions needed?
//
//	* Wrap:
//	 - SDL_Init
//	 - SDL_CreateWindow
//	 - SDL_GL_CreateContext
//	 - glewInit

int gm_initWindow(const char * winTitle,
				Uint32 win_x, Uint32 win_y, Uint32 win_w, Uint32 win_h, Uint32 min_win_w, Uint32 min_win_h)
{
	int err = SDL_Init(SDL_INIT_EVERYTHING);
	if (err)
	{
		gm_setError(ERR_MESG,"SDL Initialization error: %s",SDL_GetError());
		return EXIT_FAILURE;
	}

	gm_window = SDL_CreateWindow(winTitle, win_x, win_y, win_w, win_h,
						SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!gm_window)
	{
		gm_setError(ERR_MESG,"SDL Window creation failure: %s",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_SetWindowMinimumSize(gm_window, min_win_w, min_win_h);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	gm_glContext = SDL_GL_CreateContext(gm_window);
	if (!gm_glContext)
	{
		gm_setError(ERR_MESG,"SDL GL Context creation failure: %s",SDL_GetError());
		SDL_DestroyWindow(gm_window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		gm_setError(ERR_MESG,"Glew initialization failure: %s",glewGetErrorString(glewError));
		SDL_GL_DeleteContext(gm_glContext);
		SDL_DestroyWindow(gm_window);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, NULL);

	stbi_set_flip_vertically_on_load(true);

	gm_initializeVAO();
	glEnable(GL_DEPTH_TEST);

	//SDL_SetRelativeMouseMode(SDL_TRUE);
	//SDL_WarpMouseInWindow(gm_window,win_w/2,win_h/2);

	return EXIT_SUCCESS;
}

void gm_renderDisplay()
{
	SDL_GL_SwapWindow(gm_window);
}

void gm_renderClear(gm_Color color)
{
	static gm_Color clearColor = {};
	if (!gm_ColorEquals(clearColor,color))
	{
		clearColor = color;
		glClearColor(color.r, color.g, color.b, color.a);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gm_exit()
{
	if (gm_glContext)
	{
		SDL_GL_DeleteContext(gm_glContext);
	}
	if (gm_window)
	{
		SDL_DestroyWindow(gm_window);
	}
	SDL_Quit();
}