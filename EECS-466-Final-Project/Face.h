#pragma once
#include "Vertex.h"
#include "Vector3.h"
#include "Vector4.h"
#include "common.h"

class Face
{
public:
	std::shared_ptr<Vertex> v1;
	std::shared_ptr<Vertex> v2;
	std::shared_ptr<Vertex> v3;
	Face(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2, std::shared_ptr<Vertex> v3);
	~Face();
	void calculateVertexQsFromThisFace();
};

