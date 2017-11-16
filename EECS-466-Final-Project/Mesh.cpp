#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::calculateQs()
{
	for (auto vertex_pair : vertList)
	{
		auto vertex = vertex_pair.second;
		vertex->Q.reset();
	}
	for (std::vector<std::shared_ptr<Face>>::iterator it = faceList.begin(); it != faceList.end(); it++)
	{
		auto f = *it;
		f->calculateVertexQsFromThisFace();
	}
}

void Mesh::reduce()
{
	// Step 1 - calculate Q matrices

	auto validEdges = selectValidEdges(); // Step 2 - select all valid pairs

	/*for (auto curredge : validEdges)
	{
		std::cout << "Init cost: " << curredge->cost << std::endl;
	}*/


	//std::cout << "EDGES: " << validEdges.size() << std::endl;

	//auto edgeQueue = computeContractionTargets(validEdges); // Step 3, 4 - Compute optimal contraction targets and their errors

	for (int i = 0; i < 200; i++)
	{
		std::cout << "Loop starting" << std::endl;
		calculateQs();
		for (auto curredge : validEdges)
		{
			curredge->calculateV();
			curredge->calculateCost();
			if (curredge->cost < -1)
				std::cout << "Edge cost: " << curredge->cost << std::endl;
		}
		//std::cout << "VALID EDGES BEFORE CONTRACTION: " << validEdges.size() << std::endl;

		/*validEdgesSet::iterator testiter = validEdges.begin();
		for (; testiter != validEdges.end(); ++testiter)
		{
			auto tempEdge = *testiter;
			if (tempEdge->v1->id == 333 && tempEdge->v2->id == 334)
			{
				std::cout << "Cost from Outside: " << tempEdge->cost << std::endl;
				//std::cout << tempEdge << std::endl;
				break;
			}
		}*/
		//std::cout << "Looking at edge: " << (validEdges.begin());
		contractEdge(validEdges);

		//std::cout << "VALID EDGES AFTER CONTRACTION: " << validEdges.size() << std::endl;
		//auto validEdges2 = selectValidEdges();
		//std::cout << "NEW VALID EDGES SET AFTER CONTRACTION: " << validEdges2.size() << std::endl;
	}

	
	
}

void Mesh::contractEdge(validEdgesSet &edgesSet)
{
	//Contract edges. An edge will need to be updated if it contains v1 or v2
	auto minimum_cost_edge = get_lowest_cost_edge(edgesSet);
	auto edge_with_minimum_cost_iterator = minimum_cost_edge.first;
	auto edge_with_minimum_cost = minimum_cost_edge.second;
	edgesSet.erase(edge_with_minimum_cost_iterator);
	auto v1 = edge_with_minimum_cost->v1;
	auto v2 = edge_with_minimum_cost->v2;
	auto v = edge_with_minimum_cost->v;


	/*validEdgesSet::iterator testiter = edgesSet.begin();
	for (; testiter != edgesSet.end(); ++testiter)
	{
		auto tempEdge = *testiter;
		if (tempEdge->v1->id == 333 && tempEdge->v2->id == 334)
		{
			std::cout << "Cost from Inside: " << tempEdge->cost << std::endl;
			//std::cout << tempEdge << std::endl;
			break;
		}
	}*/

	//std::cout << "Contracting: V1 " << edge_with_minimum_cost->v1->id << " V2 " << edge_with_minimum_cost->v2->id << std::endl;;


	//std::cout << "Cost: " << edge_with_minimum_cost->cost << std::endl;
	if (edge_with_minimum_cost->cost < -1)
	{
		std::cout << "Hi";
	}

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
			++edge_check_remove_v_v1_iterator;
		}
	}

	//std::cout << "Error: " << currentEdge->cost << std::endl;

	//For each Face in faceList
	//  - Replace all instances of V1 with V
	//  - Replace all instances ov V2 with V
	//  - If the face now has two V's, delete it

	for (auto face : faceList)
	{
		//std::cout << "Replacing: " << face->v1->id << " " << face->v2->id << std::endl;
		if (face->contains(v1) && face->contains(v2))
		{
			//Delete the face
			face->deleteFace();
			//std::cout << "DELETING FACE" << std::endl;
		}
		else if (face->replace(v1, v_vertex) || face->replace(v2, v_vertex))
		{
			//std::cout << "REPLACED: " << face->v1->id << " " << face->v2->id << std::endl;
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

std::pair<validEdgesSet::iterator, std::shared_ptr<Edge>> Mesh::get_lowest_cost_edge(validEdgesSet &edgesSet)
{
	std::shared_ptr<Edge> lowest_edge = *edgesSet.begin();
	validEdgesSet::iterator lowest_iterator = edgesSet.begin();
	validEdgesSet::iterator iterator;
	for (iterator = edgesSet.begin(); iterator != edgesSet.end(); ++iterator)
	{
		auto currentEdge = *iterator;
		if (currentEdge->cost < lowest_edge->cost)
		{
			lowest_edge = currentEdge;
			lowest_iterator = iterator;
		}
	}
	return std::pair<validEdgesSet::iterator, std::shared_ptr<Edge>>(lowest_iterator, lowest_edge);
}