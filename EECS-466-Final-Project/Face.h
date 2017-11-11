#pragma once
#include "Vertex.h"
#include "Vector3.h"
#include "Vector4.h"
#include "common.h"

class Face
{
public:
	Vertex* v1;
	Vertex* v2;
	Vertex* v3;
	Face(Vertex* v1, Vertex* v2, Vertex* v3);
	~Face();
	void calculateVertexQsFromThisFace();
};

