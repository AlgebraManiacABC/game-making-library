/********************************************************************************
 * stl.c
 * 
 ********************************************************************************/

#include "stl.h"
#include "files.h"
#include "internal/object_3d.h"

#define SIZEOF_STL_TRIANGLE (14)

Object3D_t * gm_create3dObjectFromSTL(char * filename)
{
    Object3D_t * obj = malloc(sizeof(Object3D_t));
    if (!obj)
    {
        gm_setError(ERR_CODE, ERR_NOMEM);
        return NULL;
    }
    BinaryFile_t stlFile = _gm_readEntireBinaryFile(filename);
    if (stlFile.fileLength <= 0) return NULL;
    // Header is 80 bytes, triangle count immediately after as Uint32
    obj->numTriangles = *(Uint32*)(&stlFile.fileData[80]);
    if (obj->numTriangles * SIZEOF_STL_TRIANGLE + 84 > stlFile.fileLength)
    {
        gm_setError(ERR_MESG, "STL File size (%lh) inconsistent with triangle count (%lh)!",
            stlFile.fileLength,
            obj->numTriangles);
        return NULL;
    }
    obj->triangles = malloc((obj->numTriangles) * sizeof(Triangle_t));
    if (!obj->triangles)
    {
        gm_setError(ERR_CODE,ERR_NOMEM);
        return NULL;
    }
    for (int i = 0; i < obj->numTriangles; i++)
    {
        // https://docs.fileformat.com/cad/stl/
        size_t offset = 84 + (i * SIZEOF_STL_TRIANGLE);
        // REAL32[3] – Normal vector
        GLfloat norm[3] = {
            *(GLfloat*)(&stlFile.fileData[offset]),
            *(GLfloat*)(&stlFile.fileData[offset + sizeof(GLfloat)]),
            *(GLfloat*)(&stlFile.fileData[offset + 2 * sizeof(GLfloat)])
        };
        offset += sizeof(norm);
        // REAL32[3] – Vertex 1
        // REAL32[3] – Vertex 2
        // REAL32[3] – Vertex 3
        for (int j = 0; j < 3; j++)
        {
            obj->triangles[i].vertices[j].nx = norm[0];
            obj->triangles[i].vertices[j].ny = norm[1];
            obj->triangles[i].vertices[j].nz = norm[2];

            obj->triangles[i].vertices[j].x = *(GLfloat*)(&stlFile.fileData[offset]);
            offset += sizeof(GLfloat);
            obj->triangles[i].vertices[j].y = *(GLfloat*)(&stlFile.fileData[offset]);
            offset += sizeof(GLfloat);
            obj->triangles[i].vertices[j].z = *(GLfloat*)(&stlFile.fileData[offset]);
            offset += sizeof(GLfloat);
        }
        // UINT16 – Attribute byte count
        Uint16 attr = *(Uint16*)(&stlFile.fileData[offset]);
        offset += sizeof(Uint16) + attr; // Ignore attributes
    }
    return obj;
}
