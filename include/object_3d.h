/********************************************************************************
 * object_3d.h
 * 
 ********************************************************************************/

#ifndef LLGML_OBJECT_3D_H
#define LLGML_OBJECT_3D_H

#include "debug.h"

typedef struct Object3D_s Object3D_t;
typedef struct Triangle_s Triangle_t;
typedef struct Vertex_s Vertex_t;

NODISCARD
Object3D_t * gm_create3dObjectFromTriangles(Triangle_t * triangles, int numTriangles);

#endif //LLGML_OBJECT_3D_H