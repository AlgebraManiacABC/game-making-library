/********************************************************************************
 * camera.h
 * 
 ********************************************************************************/

#ifndef LLGML_CAMERA_H
#define LLGML_CAMERA_H

#include <cglm/cglm.h>
#include <stdarg.h>
#include "debug.h"

typedef struct gm_Camera_s gm_Camera_t;

// Single global camera
extern gm_Camera_t * gm_Camera;

typedef enum gm_CameraInitFlags_e
{
    GM_CAMERA_INIT_POSITION = 0b1,
    GM_CAMERA_INIT_ROTATION = 0b1 << 1,
    GM_CAMERA_INIT_FOV = 0b1 << 2

}   gm_CameraInitFlags;

/**
 * Initialize the game camera.
 * This function is "overloaded" - it can accept
 *  additional arguments, but only in a specific order.
 * The default settings are listed for each parameter
 * @param initFlags What arguments will be provided, as an OR'd list of enums
 * @param startPos The camera's starting position (vec3, {0, 0, 0})
 * @param startRot The camera's starting rotation (vec4, {0, 0, 0, 1})
 * @param startFov The camera's starting FOV (GLfloat, 90) - if zero, will be orthographic
 * @return zero on success, non-zero on failure
 */
NODISCARD
int gm_cameraInit(gm_CameraInitFlags, ...);

void gm_setCameraPos(vec3 newPos);

void gm_cameraLookAt(vec3 target, vec3 up);

void gm_rotateCamera(vec3 byAngles);

void gm_updateMatrices(const GLuint shaderProg);

void gm_printCameraMatrices();

#endif //LLGML_CAMERA_H