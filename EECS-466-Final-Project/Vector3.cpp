#include "Vector3.h"



Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3()
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}


Vector3::~Vector3()
{
}

Vector3 Vector3::operator + (Vector3 v) const
{
	return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}
Vector3 Vector3::operator - (Vector3 v) const
{
	return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}
Vector3 Vector3::operator - () const
{
	return Vector3(-this->x, -this->y, -this->z);
}

Vector3 Vector3::toUnitVector()
{
	double magnitude = sqrt(x*x + y*y + z*z);
	return Vector3(x / magnitude, y / magnitude, z / magnitude);
}

Vector3 Vector3::cross(const Vector3 v)
{
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

double Vector3::dot(const Vector3 v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::operator / (double d) const
{
	return Vector3(x / d, y / d, z / d);
}