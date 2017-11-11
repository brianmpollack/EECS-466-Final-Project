#pragma once
class ThreeMatrix
{
private:
	double matrix[3][3] = { 0.0 };
public:
	ThreeMatrix();
	~ThreeMatrix();
	double* operator[](int i);
	ThreeMatrix operator + (ThreeMatrix x) const;
};

