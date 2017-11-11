#pragma once
#include "Vertex.h"
#include "Face.h"
#include "Edge.h"
#include "common.h"
class Mesh
{
public:
	double ratio = .5;
	int delFace;
	int verts = 0, faces = 0, norms = 0;    // Number of vertices, faces and normals in the system
	//Vertex *vertList;
	std::map<int, Vertex> vertList;
	//faceStruct *faceList;
	std::vector<Face> faceList;
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edgeQueue;
	Mesh();
	~Mesh();
	void calculateQs();
	void reduce();
};

