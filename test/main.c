#include "llgml.h"

int main(int argc, char *argv[])
{
	printf("Hello world!\n");
	SDL_Window *w;
	SDL_GLContext glContext;
	gm_initWindow(SDL_INIT_EVERYTHING,SDL_WINDOW_RESIZABLE,"Hello, world!",
			SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,&w,&glContext);
	return EXIT_SUCCESS;
}