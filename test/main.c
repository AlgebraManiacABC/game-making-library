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

	vec3 startPos = {0.0f, 0.0f, 6.0f};
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
    vec3 icoPos = {0.0f, 5.0f, 0.0f};
    gm_setObjectPosition(icosahedron, icoPos);

	Object3D_t * teapot = gm_create3dObjectFromSTL("../test/teapot.stl");
	if (!teapot)
	{
	    fprintf(stderr, "%s\n", gm_getError());
	    return EXIT_FAILURE;
	}
    vec3 teapotPos = {0.0f, -1.5f, 0.0f};
    gm_setObjectPosition(teapot, teapotPos);

	float modelRotate = M_PI / (double)gm_getFrameRate();

	struct keys_s
	{
		int w, a, s, d;
		int shift, space;
		int up, down, left, right;
	};

	// Register buttons
	struct keys_s keys =
	{
		gm_registerScancode(SDL_SCANCODE_W),
		gm_registerScancode(SDL_SCANCODE_A),
		gm_registerScancode(SDL_SCANCODE_S),
		gm_registerScancode(SDL_SCANCODE_D),
		gm_registerScancode(SDL_SCANCODE_LSHIFT),
		gm_registerScancode(SDL_SCANCODE_SPACE),
		gm_registerScancode(SDL_SCANCODE_UP),
		gm_registerScancode(SDL_SCANCODE_DOWN),
		gm_registerScancode(SDL_SCANCODE_LEFT),
		gm_registerScancode(SDL_SCANCODE_RIGHT),
	};

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

		if (gm_buttonQuery(keys.w, GM_BUTTONSTATE_HELD))
			gm_moveCameraForward(deltaTime);
		if (gm_buttonQuery(keys.s, GM_BUTTONSTATE_HELD))
			gm_moveCameraBack(deltaTime);
		if (gm_buttonQuery(keys.a, GM_BUTTONSTATE_HELD))
			gm_moveCameraLeft(deltaTime);
		if (gm_buttonQuery(keys.d, GM_BUTTONSTATE_HELD))
			gm_moveCameraRight(deltaTime);
		if (gm_buttonQuery(keys.space, GM_BUTTONSTATE_HELD))
			gm_moveCameraUp(deltaTime);
		if (gm_buttonQuery(keys.shift, GM_BUTTONSTATE_HELD))
			gm_moveCameraDown(deltaTime);
		if (gm_buttonQuery(keys.up, GM_BUTTONSTATE_HELD))
			gm_rotateCameraX(-deltaTime);
		if (gm_buttonQuery(keys.down, GM_BUTTONSTATE_HELD))
			gm_rotateCameraX(deltaTime);
		if (gm_buttonQuery(keys.left, GM_BUTTONSTATE_HELD))
			gm_rotateCameraY(-deltaTime);
		if (gm_buttonQuery(keys.right, GM_BUTTONSTATE_HELD))
			gm_rotateCameraY(deltaTime);

		gm_updateCameraMatrices(shaderProg);

		gm_renderClear(GM_COLOR_BLACK);
	    gm_setWireframe(true);
		gm_renderObject(icosahedron,shaderProg);
	    gm_setWireframe(false);
		gm_rotateObjectY(icosahedron, modelRotate);
		gm_renderObject(teapot, shaderProg);

		gm_renderDisplay();

		gm_endFrame();
	}
	gm_exit();
	return EXIT_SUCCESS;
}
