#pragma once
#include "Vertex.h"
#include "ThreeMatrix.h"
#include "Vector3.h"
#include "Vector4.h"
#include "common.h"
class Edge
{
public:
	Vertex* v1;
	Vertex* v2;
	double cost = 100000;
	Vector3 v;
	bool isDeleted = false;
	Edge(Vertex* v1, Vertex* v2);
	~Edge();
	bool operator >(Edge const& e);
	friend bool operator >(Edge const& e1, Edge const& e2);
	bool operator <(Edge const& e);
	bool operator =(Edge const& e);
	void calculateV();
	void calculateCost();
};

