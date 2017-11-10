#pragma once
#include "Vertex.h"
#include "common.h"

class Face
{
public:
	Vertex* v1;
	Vertex* v2;
	Vertex* v3;
	Face(Vertex* v1, Vertex* v2, Vertex* v3);
	~Face();
};

