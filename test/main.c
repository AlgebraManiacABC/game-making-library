#include "llgml.h"

int main(int argc, char *argv[])
{
	printf("Hello world!\n");
	gm_initWindow("LLGML Test",
				SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
				800,640);
	return EXIT_SUCCESS;
}