#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::calculateQs()
{
	for (std::vector<std::shared_ptr<Face>>::iterator it = faceList.begin(); it != faceList.end(); it++)
	{
		auto f = *it;
		f->calculateVertexQsFromThisFace();
	}
}

void Mesh::reduce()
{
	for (int i = 0; i < delFace; i += 2)
	{
		std::cout << "Reducing" << std::endl;
		auto e = edgeQueue.top();
		auto v1 = e->v1;
		auto v2 = e->v2;
		int v0Index = vertList.size() + 1;
		auto v0 = std::make_shared<Vertex>(e->v.x, e->v.y, e->v.z, v0Index);
		vertList.insert(std::pair <int, std::shared_ptr<Vertex>>(v0Index, v0));

		edgeQueue.pop(); //Delete edge from queue

		e->isDeleted = true;

		for (std::vector<std::shared_ptr<Edge>>::iterator vertex1Edges = v1->edges.begin();
			vertex1Edges != v1->edges.end();
			vertex1Edges++)
		{
			auto currentEdge = *vertex1Edges;
			currentEdge->isDeleted = true;
			v0->edges.push_back(std::make_shared<Edge>(Edge(v0, currentEdge->v2)));
			currentEdge->v2->edges.push_back(std::make_shared<Edge>(Edge(currentEdge->v2, v0)));
		}

		for (std::vector<std::shared_ptr<Edge>>::iterator vertex2Edges = v2->edges.begin();
			vertex2Edges != v2->edges.end();
			vertex2Edges++)
		{
			auto currentEdge = *vertex2Edges;
			currentEdge->isDeleted = true;
			v0->edges.push_back(std::make_shared<Edge>(Edge(v0, currentEdge->v2)));
			currentEdge->v2->edges.push_back(std::make_shared<Edge>(Edge(currentEdge->v2, v0)));
		}


		v1->isDeleted = true;
		v2->isDeleted = true;

		for (std::vector<std::shared_ptr<Edge>>::iterator newEdges = v0->edges.begin();
			newEdges != v0->edges.end();
			newEdges++)
		{
			auto currentEdge = *newEdges;
			currentEdge->calculateV();
			currentEdge->calculateCost();
			edgeQueue.push(currentEdge);
		}
	}
}