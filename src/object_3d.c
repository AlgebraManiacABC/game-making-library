/********************************************************************************
 * object_3d.c
 * 
 ********************************************************************************/

#include "internal/object_3d.h"
#include "files.h"

Object3D_t * gm_create3dObjectFromTriangles(Triangle_t * triangles, int numTriangles)
{
    Object3D_t * obj = malloc(sizeof(Object3D_t));
    if (!obj)
    {
        gm_setError(ERR_CODE, ERR_NOMEM);
        return NULL;
    }
    obj->triangles = triangles;
    obj->numTriangles = numTriangles;
    return obj;
}