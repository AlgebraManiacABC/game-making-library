/********************************************************************************
 * object_3d.c
 * 
 ********************************************************************************/

#include "internal/object_3d.h"
#include "files.h"

GLuint VAO;

void gm_initializeVAO()
{
    glCreateVertexArrays(1, &VAO);
    // Positional data
    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    // Normal data
    glEnableVertexArrayAttrib(VAO, 1);
    glVertexArrayAttribBinding(VAO, 1, 0);
    glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
    // UV data
    glEnableVertexArrayAttrib(VAO, 2);
    glVertexArrayAttribBinding(VAO, 2, 0);
    glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat));

    glBindVertexArray(VAO);
}

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
    glm_mat4_identity(obj->model);
    glCreateBuffers(1, &obj->vbo);
    glNamedBufferData(obj->vbo, obj->numTriangles * sizeof(Triangle_t), obj->triangles, GL_STATIC_DRAW);
    return obj;
}

// I will be bold and decide not to include the vertex count - the highest index shouldn't exceed that count
Object3D_t * gm_create3dObjectFromVerticesAndIndices(GLfloat * vertices, size_t stride,
                                                     GLuint * indices, size_t numIndices,
                                                     bool normalsIncluded, bool uvsIncluded)
{
    // I expect vertex data to follow this pattern:
    // GLfloat[3] position
    // GLfloat[3] normal (optional)
    // GLfloat[2] uv (optional)
    // Any additional data can follow
    size_t expected_stride = 3 * sizeof(GLfloat);
    if (normalsIncluded) expected_stride += 3 * sizeof(GLfloat);
    if (uvsIncluded) expected_stride += 2 * sizeof(GLfloat);
    if (stride < expected_stride)
    {
        gm_setError(ERR_MESG, "Vertex data's stride was too small!");
        return NULL;
    }

    Object3D_t * obj = malloc(sizeof(Object3D_t));
    if (!obj)
    {
        gm_setError(ERR_CODE, ERR_NOMEM);
        return NULL;
    }
    obj->numTriangles = numIndices / 3;
    obj->triangles = calloc(obj->numTriangles, sizeof(Triangle_t));
    if (!obj->triangles)
    {
        gm_setError(ERR_CODE, ERR_NOMEM);
        return NULL;
    }
    for (int tri=0; tri<obj->numTriangles; tri++)
    {
        // Construct each triangle by copying over their vertices' information
        for (int vert=0; vert<3; vert++)
        {
            // Treat vertex as a GLfloat[stride]
            GLuint sourceIndex = indices[tri*3 + vert];
            GLfloat * sourceVertex = vertices + (sourceIndex * (stride / sizeof(GLfloat)));
            // First three floats are expected to be positional
            obj->triangles[tri].vertices[vert].x = sourceVertex[0];
            obj->triangles[tri].vertices[vert].y = sourceVertex[1];
            obj->triangles[tri].vertices[vert].z = sourceVertex[2];
            size_t offset = 3;
            if (normalsIncluded)
            {
                obj->triangles[tri].vertices[vert].nx = sourceVertex[offset++];
                obj->triangles[tri].vertices[vert].ny = sourceVertex[offset++];
                obj->triangles[tri].vertices[vert].nz = sourceVertex[offset++];
            }
            if (uvsIncluded)
            {
                obj->triangles[tri].vertices[vert].ux = sourceVertex[offset++];
                obj->triangles[tri].vertices[vert].ux = sourceVertex[offset++];
            }
        }
        // Compute normals from triangle if not provided
        if (!normalsIncluded)
        {
            GLfloat * vert1 = (vertices + indices[tri*3] * (stride / sizeof(GLfloat)));
            GLfloat * vert2 = (vertices + indices[tri*3 + 1] * (stride / sizeof(GLfloat)));
            GLfloat * vert3 = (vertices + indices[tri*3 + 2] * (stride / sizeof(GLfloat)));
            vec3 edge1, edge2;
            glm_vec3_sub(vert2, vert1, edge1);
            glm_vec3_sub(vert3, vert1, edge2);
            vec3 norm;
            glm_cross(edge1, edge2, norm);
            glm_normalize(norm);
            for (int i = 0; i < 3; i++)
            {
                obj->triangles[tri].vertices[i].nx = norm[0];
                obj->triangles[tri].vertices[i].ny = norm[1];
                obj->triangles[tri].vertices[i].nz = norm[2];
            }
        }
    }
    glm_mat4_identity(obj->model);
    glCreateBuffers(1, &obj->vbo);
    glNamedBufferData(obj->vbo, obj->numTriangles * sizeof(Triangle_t), obj->triangles, GL_STATIC_DRAW);
    return obj;
}

size_t gm_getObjectSize(Object3D_t * obj)
{
    if (!obj) return 0;
    return obj->numTriangles * sizeof(Triangle_t);
}

GLfloat * gm_getObjectData(Object3D_t * obj)
{
    if (!obj) return NULL;
    return (GLfloat*)obj->triangles;
}

size_t gm_getObjectTriangleCount(Object3D_t * obj)
{
    if (!obj) return 0;
    return obj->numTriangles;
}

void gm_moveObject(Object3D_t * obj, vec3 by)
{
    if (!obj) return;
    glm_translate(obj->model, by);
}

void gm_setObjectPosition(Object3D_t * obj, vec3 pos)
{
    if (!obj) return;
    vec3 diff;
    glm_vec3_sub(pos, obj->pos, diff);
    glm_vec3_copy(pos, obj->pos);
    glm_translate(obj->model, diff);
}

void gm_rotateObject(Object3D_t * obj, vec3 by)
{
    if (!obj) return;
    mat4 rot = GLM_MAT4_IDENTITY_INIT;
    glm_rotate_x(rot, by[0], rot);
    glm_rotate_y(rot, by[1], rot);
    glm_rotate_z(rot, by[2], rot);
    glm_mat4_mul(rot, obj->model, obj->model);
}

void gm_renderObject(Object3D_t * obj, GLuint program)
{
    if (!obj) return;

    GLuint model = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(model, 1, GL_FALSE, (GLfloat*)obj->model);
    glVertexArrayVertexBuffer(VAO, 0, obj->vbo, 0, sizeof(Vertex_t));
    glDrawArrays(GL_TRIANGLES, 0, obj->numTriangles * 3);
}