#pragma once
class Vector4
{
public:
	double x, y, z, h;
	Vector4(double x, double y, double z, double h);
	~Vector4();
	Vector4 operator + (Vector4 v) const;
	double& operator[](int i);
};

