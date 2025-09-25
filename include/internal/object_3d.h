/********************************************************************************
 * object_3d_internal.h
 * 
 ********************************************************************************/

#ifndef LLGML_OBJECT_3D_INTERNAL_H
#define LLGML_OBJECT_3D_INTERNAL_H

#include <object_3d.h>
#include <cglm/cglm.h>

struct Vertex_s
{
    GLfloat x, y, z;    // Position
    GLfloat nx, ny, nz; // Normal vector
    GLfloat ux, uy;     // UV (Texture) coordinates
};

struct Triangle_s
{
    Vertex_t vertices[3];
};

struct Object3D_s
{
    // The triangles must be contiguous in memory
    Triangle_t * triangles;
    Uint32 numTriangles;
    vec3 pos;
    mat4 model;
    GLuint vbo;
};

extern GLuint VAO;

void gm_initializeVAO();

#endif //LLGML_OBJECT_3D_INTERNAL_H