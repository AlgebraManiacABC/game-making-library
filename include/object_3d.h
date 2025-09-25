/********************************************************************************
 * object_3d.h
 * 
 ********************************************************************************/

#ifndef LLGML_OBJECT_3D_H
#define LLGML_OBJECT_3D_H

#include <cglm/ivec3.h>
#include "debug.h"

typedef struct Object3D_s Object3D_t;
typedef struct Triangle_s Triangle_t;
typedef struct Vertex_s Vertex_t;

NODISCARD
Object3D_t * gm_create3dObjectFromTriangles(Triangle_t * triangles, int numTriangles);

NODISCARD
Object3D_t * gm_create3dObjectFromVerticesAndIndices(GLfloat * vertices, size_t stride,
                                                     GLuint * indices, size_t numIndices,
                                                     bool normalsIncluded, bool uvsIncluded);

NODISCARD
size_t gm_getObjectSize(Object3D_t * obj);

NODISCARD
GLfloat * gm_getObjectData(Object3D_t * obj);

NODISCARD
size_t gm_getObjectTriangleCount(Object3D_t * obj);

void gm_moveObject(Object3D_t * obj, vec3 by);
void gm_setObjectPosition(Object3D_t * obj, vec3 pos);
void gm_rotateObject(Object3D_t * obj, vec3 by);

void gm_renderObject(Object3D_t * obj, GLuint program);

#endif //LLGML_OBJECT_3D_H