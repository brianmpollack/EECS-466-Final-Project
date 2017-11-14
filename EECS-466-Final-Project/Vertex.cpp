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

void Vertex::addNormal(float x, float y, float z)
{
	this->normX += x;
	this->normY += y;
	this->normZ += z;
	this->normCount++;
}

bool Vertex::operator<(Vertex const& v) const
{
	return this->id < v.id;
}
bool Vertex::operator>(Vertex const& v) const
{
	return this->id > v.id;
}