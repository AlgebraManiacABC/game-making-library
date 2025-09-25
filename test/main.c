#include "llgml.h"

int main(int argc, char *argv[])
{
	if (argc > 1) printf("Hello world! (%s)\n",argv[1]);
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

	const GLuint vert = gm_createShader("../shaders/perspective.vert", GL_VERTEX_SHADER);
	const GLuint frag = gm_createShader("../shaders/normals.frag", GL_FRAGMENT_SHADER);
	if (! vert || ! frag)
	{
		fprintf(stderr, "%s\n", gm_getError());
		return EXIT_FAILURE;
	}
	const GLuint shaderProg = gm_createShaderProgram(2, vert, frag);
	if (!shaderProg)
	{
		fprintf(stderr, "%s\n", gm_getError());
		return EXIT_FAILURE;
	}
	gm_setActiveShaderProgram(shaderProg);

	gm_setFrameRate(60.0f);

	vec3 startPos = {0.0, 0.0, 6};
	err = gm_cameraInit(GM_CAMERA_INIT_POSITION, startPos);
	if (err)
	{
		fprintf(stderr, "%s\n", gm_getError());
		return EXIT_FAILURE;
	}

	Object3D_t * icosahedron = gm_create3dObjectFromVerticesAndIndices(
		icosahedron_vertices, 3 * sizeof(GLfloat),
		icosahedron_indices, sizeof(icosahedron_indices) / sizeof(GLfloat),
		false, false
	);
    vec3 icoPos = {0.0, 5.0, 0.0};
    gm_setObjectPosition(icosahedron, icoPos);

	Object3D_t * teapot = gm_create3dObjectFromSTL("../test/teapot.stl");
	if (!teapot)
	{
	    fprintf(stderr, "%s\n", gm_getError());
	    return EXIT_FAILURE;
	}
    vec3 teapotPos = {0.0, -1.5, 0.0};
    gm_setObjectPosition(teapot, teapotPos);

	vec3 rotateRad = {0, (float)(M_PI / (double)gm_getFrameRate()), 0};
	while(true)
	{
		gm_beginFrame();

		err = gm_handleEvents();
		if (err == GM_QUIT) break;
		if (err == GM_ERROR)
		{
			fprintf(stderr, "%s\n", gm_getError());
			return EXIT_FAILURE;
		}

		gm_renderClear(GM_COLOR_BLACK);

		gm_updateMatrices(shaderProg);
		gm_renderObject(icosahedron,shaderProg);
		gm_rotateObject(icosahedron, rotateRad);
		gm_renderObject(teapot, shaderProg);

		gm_renderDisplay();

		gm_endFrame();
	}
	gm_exit();
	return EXIT_SUCCESS;
}
