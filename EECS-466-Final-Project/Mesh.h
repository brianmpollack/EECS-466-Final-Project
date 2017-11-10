#pragma once
#include "Vertex.h"
#include "Face.h"
#include "common.h"
class Mesh
{
public:
	int verts = 0, faces = 0, norms = 0;    // Number of vertices, faces and normals in the system
	//Vertex *vertList;
	std::map<int, Vertex> vertList;
	//faceStruct *faceList;
	std::vector<Face> faceList;
	Mesh();
	~Mesh();
};

