#include "Vector4.h"



Vector4::Vector4(double x, double y, double z, double h)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->h = h;
}


Vector4::~Vector4()
{
}

Vector4 Vector4::operator + (Vector4 v) const
{
	return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->h + v.h);
}

double& Vector4::operator[](int i)
{
	if (i == 0) return x;
	if (i == 1) return y;
	if (i == 2) return z;
	if (i == 3) return h;
}