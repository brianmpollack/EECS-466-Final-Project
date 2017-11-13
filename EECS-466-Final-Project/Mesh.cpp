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

/*void Mesh::reduce()
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
}*/

void Mesh::reduce()
{
	calculateQs(); // Step 1 - calculate Q matrices

	auto validEdges = selectValidEdges(); // Step 2 - select all valid pairs

	std::cout << "EDGES: " << validEdges.size() << std::endl;

	auto edgeQueue = computeContractionTargets(validEdges); // Step 3 - Compute optimal contraction targets and their errors

	std::cout << "EDGE QUEUE: " << edgeQueue.size() << std::endl;

	for (int i = 0; i < 45; i++)
	{ //For debugging, print the vertices and the optimal contraction target. TODO: REMOVE
		std::cout << "V1: " << validEdges[i]->v1->x << "," << validEdges[i]->v1->y << "," << validEdges[i]->v1->z << ";  ";
		std::cout << "V2: " << validEdges[i]->v2->x << "," << validEdges[i]->v2->y << "," << validEdges[i]->v2->z << ";  ";
		std::cout << "V: " << validEdges[i]->v.x << "," << validEdges[i]->v.y << "," << validEdges[i]->v.z;
		std::cout << std::endl;
	}
	
}

std::vector<std::shared_ptr<Edge>> Mesh::selectValidEdges()
{
	//TODO: Currently this returns 2*number of real edges (both ways for each)
	std::vector<std::shared_ptr<Edge>> validEdges;
	for (auto currentVertex : vertList)
	{
		for (auto currentEdge : currentVertex.second->edges)
		{
			validEdges.push_back(currentEdge);
		}
	}
	return validEdges;
}

std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeComparisonMinPriorityQueue> Mesh::computeContractionTargets(std::vector<std::shared_ptr<Edge>> validEdges)
{
	std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeComparisonMinPriorityQueue> edgeQueue;
	for (auto currentEdge : validEdges)
	{
		currentEdge->calculateV();
		currentEdge->calculateCost();
		edgeQueue.push(currentEdge);
	}
	return edgeQueue;
}