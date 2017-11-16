#pragma once
#include "common.h"
#include "Vertex.h"

class Edge
{
public:
	void calculateV();
	void calculateCost();
	std::shared_ptr<Vertex> v1;
	std::shared_ptr<Vertex> v2;
	double cost = 100000; //TODO this should be 0 I believe?
	Vector3 v;
	bool isDeleted = false;
	Edge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);
	~Edge();
	//bool operator >(Edge const& e);
	//friend bool operator >(Edge const& e1, Edge const& e2);
	bool operator <(Edge const& e);
	//bool operator =(Edge const& e);
	
	bool contains(const std::shared_ptr<Vertex> v) const;
	
	bool CompareEdgesByCost(const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b);
};
struct CompareEdgesInSharedPointer
{
	bool operator() (const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b)
	{
		return *a < *b;
	}
};
/*struct CompareEdgesByCost
{
	bool operator() (const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b)
	{
		return (*a).cost < (*b).cost;
	}
};*/