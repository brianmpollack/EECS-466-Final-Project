#include "Edge.h"



Edge::Edge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2)
{
	//Enforce edge v1 always < v2
	if (v1->id < v2->id)
	{
		this->v1 = v1;
		this->v2 = v2;
	}
	else
	{
		this->v1 = v2;
		this->v2 = v1;
	}
	
}


Edge::~Edge()
{
}

/*bool Edge::operator >(Edge const& e)
{
	return this->cost > e.cost;
}*/
/*bool operator>(Edge const & e1, Edge const & e2)
{
	return e1.cost > e2.cost;
}*/
/*bool Edge::operator <(Edge const& e)
{
	return this->cost < e.cost;
}*/
/*bool Edge::operator =(Edge const& e)
{
	return this->cost = e.cost;
}*/

void Edge::calculateV()
{
	//Calculate new vertex position
	Vector3 v1Vector = Vector3(v1->x, v1->y, v1->z);
	Vector3 v2Vector = Vector3(v2->x, v2->y, v2->z);

	FourMatrix vertexDelta = v1->Q + v2->Q;
	vertexDelta[3][0] = 0;
	vertexDelta[3][1] = 0;
	vertexDelta[3][2] = 0;
	vertexDelta[3][3] = 1;

	//Vector4 ans = vertexDelta.solveSystem(Vector4(0, 0, 0, 1));
	try {
		Vector4 ans = vertexDelta.inverse() * Vector4(0, 0, 0, 1);
		this->v = Vector3(ans.x, ans.y, ans.z);
	}
	catch (const std::domain_error& e)
	{
		//If we couldn't calculate a point, just use the midpoint
		this->v = (v1Vector + v2Vector) / 2;
	} //TODO: Do we want to also do the endpoints? (See circled section at end of part 4.0)
		
}

void Edge::calculateCost()
{
	//Section 4.1 step 3
	//v_transpose * (Q1+Q2) * v

	//TODO: Do we need something here saying cost is 0 if this edge doesn't lead to a contraction?

	FourMatrix vertexDelta = v1->Q + v2->Q;

	Vector4 V_vec4(this->v.x, this->v.y, this->v.z, 1.0);

	this->cost = 0;
	for (int i = 0; i < 4; i++)
	{
		double temp_cost = 0;
		for (int j = 0; j < 4; j++)
		{
			temp_cost += V_vec4[j] * vertexDelta[i][j];
		}
		this->cost += temp_cost * V_vec4[i];
	}
}
