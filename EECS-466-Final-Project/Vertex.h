#pragma once
#include "common.h"
#include "Edge.h"

class Vertex
{
public:
	int id = -1;
	float x=0, y=0, z=0;
	float normX=0, normY=0, normZ=0;
	int normCount=0;
	bool isDeleted = false;
	//std::map<int, std::shared_ptr<Vertex>> neighboringVertices;
	Vertex();
	Vertex(float x, float y, float z, int id);
	~Vertex();
	bool operator<(Vertex const& v) const;
	bool operator>(Vertex const& v) const;
	//void initialize(float x, float y, float z);
	void addNormal(float x, float y, float z);
	FourMatrix Q;
};