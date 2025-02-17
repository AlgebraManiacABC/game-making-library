#ifndef POLY_H
#define POLY_H

#include "math.h"

static const GLdouble phi = 0x3FF9E3779B97F4A8;

GLfloat icosahedron_vertices[] =
{
	// Z == 0
	 phi,  1.0,  0.0, //  0
	 phi, -1.0,  0.0, //  1
	-phi, -1.0,  0.0, //  2
	-phi,  1.0,  0.0, //  3
	// Y == 0
	 1.0,  0.0,  phi, //  4
	-1.0,  0.0,  phi, //  5
	-1.0,  0.0, -phi, //  6
	 1.0,  0.0, -phi, //  7
	 // X == 0
	  0.0,  phi,  1.0, //  8
	  0.0,  phi, -1.0, //  9
	  0.0, -phi, -1.0, // 10
	  0.0, -phi,  1.0, // 11
};

GLuint icosahedron_indices[] =
{
	0, 8, 9,
	3, 9, 8,
	0, 9, 7,
	0, 4, 9,
	3, 6, 7,
	3, 8, 5,
	4, 5, 8,
	6, 7, 9,
	2, 6, 3,
	2, 3, 5,
	0, 7, 1,
	0, 1, 4,
	1, 11, 4,
	1, 10, 11,
	1, 7, 10,
	6, 10, 7,
	2, 10, 6,
	2, 11, 10,
	2, 5, 11,
	4, 11, 5,
};

#endif