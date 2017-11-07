#pragma once
#include "common.h"

class MeshReader
{
private:
	int verts=0, faces=0, norms=0;    // Number of vertices, faces and normals in the system
	point *vertList, *normList; // Vertex and Normal Lists
	faceStruct *faceList;	    // Face List
	char* filename;
	float sign = 1;
public:
	MeshReader();
	void setFilename(char* filename);
	void read();
	void draw();
};

