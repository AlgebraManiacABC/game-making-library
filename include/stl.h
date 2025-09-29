/********************************************************************************
 * stl.h
 * 
 ********************************************************************************/

#ifndef STL_H
#define STL_H

#include "debug.h"
#include "object_3d.h"

NODISCARD
Object3D_t * gm_create3dObjectFromSTL(char * filename);

#endif