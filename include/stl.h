/********************************************************************************
 * stl.h
 * 
 ********************************************************************************/

#ifndef LLGML_STL_H
#define LLGML_STL_H

#include "debug.h"
#include "object_3d.h"

NODISCARD
Object3D_t * gm_create3dObjectFromSTL(char * filename);

#endif //LLGML_STL_H