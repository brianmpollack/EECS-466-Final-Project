#include "Vertex.h"



Vertex::Vertex()
{
	
}

Vertex::Vertex(float x, float y, float z, int id)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->id = id;
}


Vertex::~Vertex()
{
}

/*void Vertex::initialize(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}*/

void Vertex::addNormal(float x, float y, float z)
{
	this->normX += x;
	this->normY += y;
	this->normZ += z;
	this->normCount++;
}

bool Vertex::isConnectedTo(const Vertex* v)
{
	//std::cout << "Checking ID: " << id << " against ID: " << v->id << std::endl;
	std::vector<Edge>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		Vertex* currentVertex = (*it).v2;
		//std::cout << "     " << currentVertex.id << std::endl;
		if (currentVertex->id == v->id) return true;
	}
	return false;
}