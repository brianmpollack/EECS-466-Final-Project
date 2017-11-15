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

	//auto edgeQueue = computeContractionTargets(validEdges); // Step 3, 4 - Compute optimal contraction targets and their errors

	for (int i = 0; i < 300; i++)
	{

		std::cout << "VALID EDGES BEFORE CONTRACTION: " << validEdges.size() << std::endl;

		contractEdge(validEdges);

		//std::cout << "VALID EDGES AFTER CONTRACTION: " << validEdges.size() << std::endl;
		//auto validEdges2 = selectValidEdges();
		//std::cout << "NEW VALID EDGES SET AFTER CONTRACTION: " << validEdges2.size() << std::endl;
	}

	
	
}

void Mesh::contractEdge(validEdgesSet &edgesSet)
{
	//Contract edges. An edge will need to be updated if it contains v1 or v2
	auto edge_with_minimum_cost_iterator = std::min_element(edgesSet.begin(), edgesSet.end(), [](const std::shared_ptr<Edge>& a, const std::shared_ptr<Edge>& b) {
		return (*a).cost < (*b).cost;
	});
	//auto edge_with_minimum_cost_iterator = edgesSet.begin();
	auto edge_with_minimum_cost = *edge_with_minimum_cost_iterator;
	edgesSet.erase(edge_with_minimum_cost_iterator);
	auto v1 = edge_with_minimum_cost->v1;
	auto v2 = edge_with_minimum_cost->v2;
	auto v = edge_with_minimum_cost->v;


	//Make vertex for V
	auto v_vertex = this->create_vertex(v);

	//Delete all edges that have vertex V
	validEdgesSet::iterator edge_check_remove_v_v1_iterator = edgesSet.begin();
	//for (auto edge_check_remove_v_v1 : edgesSet)
	while (edge_check_remove_v_v1_iterator != edgesSet.end())
	{
		auto edge_check_remove_v_v1 = *edge_check_remove_v_v1_iterator;
		if (edge_check_remove_v_v1->contains(v1))
		{
			edge_check_remove_v_v1_iterator = edgesSet.erase(edge_check_remove_v_v1_iterator);
			//std::cout << "Contains V1" << std::endl;
		}
		else if (edge_check_remove_v_v1->contains(v2))
		{
			edge_check_remove_v_v1_iterator = edgesSet.erase(edge_check_remove_v_v1_iterator);
			//std::cout << "Contains V2" << std::endl;
		}
		else
		{
			edge_check_remove_v_v1_iterator++;
		}
	}

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
		else if (face->replace(v1, v_vertex) || face->replace(v2, v_vertex))
		{
			// If V1 or V2 was replaced with V on this face, add all of the face's Edges to the new contraction target queue
			auto new_edge_1 = std::make_shared<Edge>(face->v1, face->v2);
			edgesSet.insert(new_edge_1);
			auto new_edge_2 = std::make_shared<Edge>(face->v1, face->v3);
			edgesSet.insert(new_edge_2);
			auto new_edge_3 = std::make_shared<Edge>(face->v2, face->v3);
			edgesSet.insert(new_edge_3);
			//std::cout << "Updated face" << std::endl;
		}
	}
}

validEdgesSet Mesh::selectValidEdges()
{
	// TODO: This currenly only selects edges, not close vertices
	//std::vector<std::shared_ptr<Edge>> validEdges;
	validEdgesSet validEdges;
	for (auto face : faceList)
	{
		if (face->deleted == true) continue;
		validEdges.insert(std::make_shared<Edge>(face->v1, face->v2));
		validEdges.insert(std::make_shared<Edge>(face->v1, face->v3));
		validEdges.insert(std::make_shared<Edge>(face->v2, face->v3));
	}
	return validEdges;
}

/*contractionTargetsPriorityQueue Mesh::computeContractionTargets(validEdgesSet validEdges)
{
	contractionTargetsPriorityQueue edgeQueue;
	for (auto currentEdge : validEdges)
	{
		currentEdge->calculateV();
		currentEdge->calculateCost();
		edgeQueue.push(currentEdge);
	}
	return edgeQueue;
}*/

std::shared_ptr<Vertex> Mesh::create_vertex(Vector3& v)
{
	std::shared_ptr<Vertex> newVertex = std::make_shared<Vertex>(v.x, v.y, v.z, vertList.size() + 1);
	vertList.insert(std::pair<int, std::shared_ptr<Vertex>>(newVertex->id, newVertex));
	return newVertex;
}