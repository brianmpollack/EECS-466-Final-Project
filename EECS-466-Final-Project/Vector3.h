#pragma once
#include "common.h"
class Vector3
{
public:
	double x, y, z;
	Vector3(double x, double y, double z);
	Vector3();
	~Vector3();

	double dot(const Vector3 v);
	Vector3 cross(const Vector3 v);
	Vector3 toUnitVector();

	Vector3 operator + (Vector3 v) const;
	Vector3 operator - (Vector3 v) const;
	Vector3 operator - () const;
	Vector3 operator / (double d) const;
};

