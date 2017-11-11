#pragma once
#include "common.h"
class FourMatrix
{
private:
	double matrix[4][4] = { 0.0 };
public:
	FourMatrix();
	~FourMatrix();
	double* operator[] (int i);
	FourMatrix operator + (FourMatrix x) const;
	FourMatrix operator * (const double d) const;
	Vector4 operator * (Vector4 v) const;
	FourMatrix inverse() const;
};

