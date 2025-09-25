/********************************************************************************
 * camera.c
 * 
 ********************************************************************************/

#include "camera.h"
#include "debug.h"
#include "window.h"

struct gm_Camera_s
{
    vec3 pos;
    versor rot; // quaternion
    float fov; // if 0, orthographic
    mat4 view;
    mat4 proj;

} * gm_Camera;

int gm_cameraInit(gm_CameraInitFlags flags, ...)
{
    va_list args;
    va_start(args, flags);

    vec3 startPos = {0, 0, 0};
    if (flags & GM_CAMERA_INIT_POSITION)
    {
        glm_vec3_copy(va_arg(args, vec3), startPos);
    }

    vec4 startRot = {0, 0, 0, 1};
    if (flags & GM_CAMERA_INIT_ROTATION)
    {
        glm_quat_copy(va_arg(args, versor), startRot);
    }

    GLfloat startFOV = 90.0f;
    if (flags & GM_CAMERA_INIT_FOV)
    {
        startFOV = va_arg(args, GLdouble);
        glm_clamp(startFOV, 0.0f, 90.0f);
    }

    gm_Camera = malloc(sizeof(gm_Camera_t));
    if (!gm_Camera)
    {
        gm_setError(ERR_CODE, ERR_NOMEM);
        return EXIT_FAILURE;
    }

    va_end(args);

    glm_vec3_copy(startPos, gm_Camera->pos);
    glm_quat_copy(startRot, gm_Camera->rot);
    gm_Camera->fov = startFOV;
    glm_quat_look(gm_Camera->pos, gm_Camera->rot, gm_Camera->view);
    glm_perspective(startFOV, GM_ASPECTRATIO, 0.1f, 100.0f, gm_Camera->proj);

    return EXIT_SUCCESS;
}

void gm_setCameraPos(vec3 newPos)
{
    vec3 diff;
    glm_vec3_sub(newPos, gm_Camera->pos, diff);
    glm_vec3_copy(newPos, gm_Camera->pos);
    glm_translate(gm_Camera->view, diff);
}

void gm_cameraLookAt(vec3 target, vec3 up)
{
    glm_lookat(gm_Camera->pos, target, up, gm_Camera->view);
}

void gm_rotateCamera(vec3 byAngles)
{
    mat4 rot = GLM_MAT4_IDENTITY_INIT;
    glm_rotate_x(rot,byAngles[0], rot);
    glm_rotate_y(rot,byAngles[1], rot);
    glm_rotate_z(rot,byAngles[2], rot);
    glm_mat4_mul(rot, gm_Camera->view, gm_Camera->view);
}

void gm_updateMatrices(const GLuint shaderProg)
{
    const GLint viewLoc = glGetUniformLocation(shaderProg, "view");
    if (viewLoc < 0)
    {
        gm_setError(ERR_MESG, "View matrix uniform was not found!");
        return;
    }
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat*)gm_Camera->view);
    const GLint projLoc = glGetUniformLocation(shaderProg, "proj");
    if (projLoc < 0)
    {
        gm_setError(ERR_MESG, "Projection matrix uniform was not found!");
        return;
    }
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (GLfloat*)gm_Camera->proj);

}

void gm_printCameraMatrices()
{
    printf("Position: ");
    print1dFloatArrayAsTable(gm_Camera->pos, 1, 3);
    printf("View:\n");
    print1dFloatArrayAsTable((float*)gm_Camera->view, 4, 4);
    printf("Projection:\n");
    print1dFloatArrayAsTable((float*)gm_Camera->proj, 4, 4);
}