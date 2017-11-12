#pragma once
#include "common.h"
#include "Vertex.h"

class Edge
{
public:
	std::shared_ptr<Vertex> v1;
	std::shared_ptr<Vertex> v2;
	double cost = 100000; //TODO this should be 0 I believe?
	Vector3 v;
	bool isDeleted = false;
	Edge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);
	~Edge();
	//bool operator >(Edge const& e);
	//friend bool operator >(Edge const& e1, Edge const& e2);
	//bool operator <(Edge const& e);
	//bool operator =(Edge const& e);
	void calculateV();
	void calculateCost();
};

class EdgeComparison
{
public:
	bool operator() (std::shared_ptr<Edge> v1, std::shared_ptr<Edge> v2)
	{
		return v1->cost > v2->cost;
	}
};