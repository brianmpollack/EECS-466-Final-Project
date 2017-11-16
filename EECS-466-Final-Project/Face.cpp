#include "Face.h"



Face::Face(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2, std::shared_ptr<Vertex> v3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
}


Face::~Face()
{
}

void Face::calculateVertexQsFromThisFace()
{
	//Calculate Kp for this face and add it to each vertex's Q value
	Vector3 v1Vector = Vector3(v1->x, v1->y, v1->z);
	Vector3 v2Vector = Vector3(v2->x, v2->y, v2->z);
	Vector3 v3Vector = Vector3(v3->x, v3->y, v3->z);
	
	Vector3 normal = (v2Vector - v1Vector).cross(v3Vector - v1Vector).toUnitVector();

	Vector4 v1Q = Vector4(normal.x, normal.y, normal.z, -(v1Vector.dot(normal)));
	Vector4 v2Q = Vector4(normal.x, normal.y, normal.z, -(v2Vector.dot(normal)));
	Vector4 v3Q = Vector4(normal.x, normal.y, normal.z, -(v3Vector.dot(normal)));

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			v1->Q[i][j] += v1Q[i] * v1Q[j];
			v2->Q[i][j] += v2Q[i] * v2Q[j];
			v3->Q[i][j] += v3Q[i] * v3Q[j];
		}
	}
}

bool Face::contains(const std::shared_ptr<Vertex> v) const
{
	if ((v1->id == v->id) || (v2->id == v->id) || (v3->id == v->id))
		return true;
	return false;
}

void Face::deleteFace()
{
	this->deleted = true;
}

bool Face::replace(const std::shared_ptr<Vertex> replace, const std::shared_ptr<Vertex> with)
{
	if (this->v1->id == replace->id)
	{
		this->v1 = with;
		return true;
	}
	else if (this->v2->id == replace->id)
	{
		this->v2 = with;
		return true;
	}
	else if (this->v3->id == replace->id)
	{
		this->v3 = with;
		return true;
	}
	return false;
}