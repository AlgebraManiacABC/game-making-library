#include "llgml.h"

int main(int argc, char *argv[])
{
	printf("Hello world!\n");
	int err = EXIT_SUCCESS;
	err = gm_initWindow("LLGML Test",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			1280, 720,
			50, 50);
	if (err != EXIT_SUCCESS)
	{
		fprintf(stderr, "%s\n", gm_getError());
		return EXIT_FAILURE;
	}

	GLuint shaderProg = gm_createShaderProgram(2,
		gm_createShader("../shaders/xyz.vert", GL_VERTEX_SHADER),
		gm_createShader("../shaders/white.frag", GL_FRAGMENT_SHADER));
	if (!shaderProg)
	{
		fprintf(stderr, "%s\n", gm_getError());
		return EXIT_FAILURE;
	}
	gm_setActiveShaderProgram(shaderProg);

	gm_setFrameRate(60.0f);

	Object3D_t * teapot = gm_create3dObjectFromSTL("../test/teapot.stl");
	if (teapot == NULL)
	{
		fprintf(stderr, "%s\n", gm_getError());
		return EXIT_FAILURE;
	}

	while(true)
	{
		gm_beginFrame();

		err = gm_handleEvents();
		if (err != EXIT_SUCCESS) break;

		gm_renderClear(GM_COLOR_BLACK);
		gm_renderDisplay();

		gm_endFrame();
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