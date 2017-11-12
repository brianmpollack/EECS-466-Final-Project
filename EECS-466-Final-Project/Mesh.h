#pragma once
#include "common.h"
#include "Vertex.h"
#include "Face.h"
#include "Edge.h"

class Mesh
{
public:
	double ratio = .5;
	int delFace;
	int verts = 0, faces = 0, norms = 0;    // Number of vertices, faces and normals in the system
	//Vertex *vertList;
	std::map<int, std::shared_ptr<Vertex>> vertList;
	//faceStruct *faceList;
	std::vector<std::shared_ptr<Face>> faceList;
	std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge>>, EdgeComparison> edgeQueue;
	Mesh();
	~Mesh();
	void calculateQs();
	void reduce();
};

