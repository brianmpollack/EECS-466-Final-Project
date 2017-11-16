#pragma once
#include "Vertex.h"
#include "Vector3.h"
#include "Vector4.h"
#include "common.h"

class Face
{
public:
	bool deleted = false;
	std::shared_ptr<Vertex> v1;
	std::shared_ptr<Vertex> v2;
	std::shared_ptr<Vertex> v3;
	Face(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2, std::shared_ptr<Vertex> v3);
	~Face();
	void calculateVertexQsFromThisFace();
	bool contains(const std::shared_ptr<Vertex> v) const;
	void deleteFace();
	bool replace(const std::shared_ptr<Vertex> replace, const std::shared_ptr<Vertex> with);
};

