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
	calculateQs(); // Step 1 - calculate Q matrices

	auto validEdges = selectValidEdges(); // Step 2 - select all valid pairs

	std::cout << "EDGES: " << validEdges.size() << std::endl;

	auto edgeQueue = computeContractionTargets(validEdges); // Step 3, 4 - Compute optimal contraction targets and their errors

	std::cout << "EDGE QUEUE: " << edgeQueue.size() << std::endl;
	
	contractEdges(edgeQueue);
	
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

		//std::cout << "Error: " << currentEdge->cost << std::endl;

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
	// TODO: This currenly only selects edges, not close vertices
	//std::vector<std::shared_ptr<Edge>> validEdges;
	validEdgesSet validEdges;
	for (auto face : faceList)
	{
		validEdges.insert(std::make_shared<Edge>(face->v1, face->v2));
		validEdges.insert(std::make_shared<Edge>(face->v1, face->v3));
		validEdges.insert(std::make_shared<Edge>(face->v2, face->v3));
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