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

	auto edgeQueue = computeContractionTargets(validEdges); // Step 3, 4 - Compute optimal contraction targets and their errors

	std::cout << "EDGE QUEUE: " << edgeQueue.size() << std::endl;
	
	contractEdges(edgeQueue);

	/*int i = 0;
	for (auto edge : validEdges)
	{
		if (i == 45) break;
		std::cout << "V1: " << edge->v1->x << "," << edge->v1->y << "," << edge->v1->z << ";  ";
		std::cout << "V2: " << edge->v2->x << "," << edge->v2->y << "," << edge->v2->z << ";  ";
		std::cout << "V: " << edge->v.x << "," << edge->v.y << "," << edge->v.z;
		std::cout << std::endl;
		i++;
	}*/
	
}

contractionTargetsPriorityQueue Mesh::contractEdges(contractionTargetsPriorityQueue edgeQueue)
{
	for (int i = 0; i < 2200; i++)
	{
		auto currentEdge = edgeQueue.top();
		edgeQueue.pop();
		auto v1 = currentEdge->v1;
		auto v2 = currentEdge->v2;
		auto v = currentEdge->v;

		//Make vertex for V
		auto v_vertex = this->create_vertex(v);

		std::cout << "Error: " << currentEdge->cost << std::endl;

		//For each Face in faceList
		//  - Replace all instances of V1 with V
		//  - Replace all instances ov V2 with V
		//  - If the face now has two V's, delete it

		for (auto face : faceList)
		{
			if (face->contains(v1) && face->contains(v2))
			{
				//Delete the face
				face->deleteFace();
				//std::cout << "DELETING FACE" << std::endl;
			}
			else
			{
				face->replace(v1, v_vertex);
				face->replace(v2, v_vertex);
			}
				
		}
	}
	return edgeQueue;
}

validEdgesSet Mesh::selectValidEdges()
{
	//TODO: Currently this returns 2*number of real edges (both ways for each)
	// TODO: This currenly only selects edges, not close vertices
	//std::vector<std::shared_ptr<Edge>> validEdges;
	validEdgesSet validEdges;
	for (auto currentVertex : vertList)
	{
		for (auto currentNeighboringPair : currentVertex.second->neighboringVertices)
		{
			auto currentNeighbor = currentNeighboringPair.second;
			std::shared_ptr<Edge> currentEdge = std::make_shared<Edge>(currentVertex.second, currentNeighbor);
			validEdges.insert(currentEdge);
		}
	}
	return validEdges;
}

contractionTargetsPriorityQueue Mesh::computeContractionTargets(validEdgesSet validEdges)
{
	contractionTargetsPriorityQueue edgeQueue;
	for (auto currentEdge : validEdges)
	{
		currentEdge->calculateV();
		currentEdge->calculateCost();
		edgeQueue.push(currentEdge);
	}
	return edgeQueue;
}

std::shared_ptr<Vertex> Mesh::create_vertex(Vector3& v)
{
	std::shared_ptr<Vertex> newVertex = std::make_shared<Vertex>(v.x, v.y, v.z, vertList.size() + 1);
	vertList.insert(std::pair<int, std::shared_ptr<Vertex>>(newVertex->id, newVertex));
	return newVertex;
}