#include "llgml.h"

int main(int argc, char *argv[])
{
	printf("Hello world!\n");
	int err = EXIT_SUCCESS;
	err = gm_initWindow("LLGML Test",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			1280, 720);
	if (err != EXIT_SUCCESS)
	{
		fprintf(stderr, "%s\n", gm_getError());
		return EXIT_FAILURE;
	}
	while ( (err = gm_handleEvents()) == EXIT_SUCCESS)
	{
		gm_renderClear();
		gm_renderDisplay();
	}
	if (err == GM_ERROR)
	{
		fprintf(stderr, "%s\n", gm_getError());
		gm_exit();
		return EXIT_FAILURE;
	}
	gm_exit();
	return EXIT_SUCCESS;
}