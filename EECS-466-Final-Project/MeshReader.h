#pragma once
#include "Mesh.h"
#include "Vertex.h"
#include "common.h"

class MeshReader
{
private:
	Mesh mesh;
	char* filename;
	float sign = 1;
public:
	MeshReader();
	void setFilename(char* filename);
	void read();
	void draw(float x_trans=0.0, float y_trans=0.0);
	void collapse();
};

