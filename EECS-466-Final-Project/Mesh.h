#pragma once
#include "common.h"
#include "Vertex.h"
#include "Face.h"
#include "Edge.h"

//typedef std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, CompareEdgesByCost> contractionTargetsPriorityQueue;
typedef std::set<std::shared_ptr<Edge>, CompareEdgesInSharedPointer> validEdgesSet;

class Mesh
{
private:
	validEdgesSet selectValidEdges();
	//contractionTargetsPriorityQueue computeContractionTargets(validEdgesSet validEdges);
	void contractEdge(validEdgesSet &edgesSet);
	std::shared_ptr<Vertex> create_vertex(Vector3& v);
	std::pair<validEdgesSet::iterator, std::shared_ptr<Edge>> get_lowest_cost_edge(validEdgesSet &edgesSet);
public:
	int delFace;
	int verts = 0, faces = 0, norms = 0;    // Number of vertices, faces and normals in the system
	//Vertex *vertList;
	std::map<int, std::shared_ptr<Vertex>> vertList;
	//faceStruct *faceList;
	std::vector<std::shared_ptr<Face>> faceList;
	Mesh();
	~Mesh();
	void calculateQs();
	void reduce(float ratio=0.6);
};

