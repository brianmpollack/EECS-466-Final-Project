#pragma once
#include "common.h"
class Mesh
{
public:
	int verts = 0, faces = 0, norms = 0;    // Number of vertices, faces and normals in the system
	point *vertList, *normList; // Vertex and Normal Lists
	faceStruct *faceList;	    // Face List
	Mesh();
	~Mesh();
};

