#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::calculateQs()
{
	for (std::vector<Face>::iterator it = faceList.begin(); it != faceList.end(); it++)
	{
		Face f = *it;
		f.calculateVertexQsFromThisFace();
	}
}

void Mesh::reduce()
{
	for (int i = 0; i < delFace; i += 2)
	{
		Edge e = edgeQueue.top();
		Vertex* v1 = e.v1;
		Vertex* v2 = e.v2;
		int v0Index = vertList.size() + 1;
		Vertex v0 = Vertex(e.v.x, e.v.y, e.v.z, v0Index);
		vertList.insert(std::pair <int, Vertex>(v0Index, v0));

		edgeQueue.pop(); //Delete edge from queue

		std::vector<Vertex*> newConnectedVertices();
		e.isDeleted = true;

		for (std::vector<Vertex*>::iterator vertex1Neighbors = v1->connectedVertices.begin();
			vertex1Neighbors != v1->connectedVertices.end();
			vertex1Neighbors++)
		{

		}
	}
}