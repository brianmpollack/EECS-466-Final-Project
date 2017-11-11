#include "ThreeMatrix.h"



ThreeMatrix::ThreeMatrix()
{
}


ThreeMatrix::~ThreeMatrix()
{
}

double* ThreeMatrix::operator[](int i)
{
	return this->matrix[i];
}

ThreeMatrix ThreeMatrix::operator + (ThreeMatrix x) const
{
	ThreeMatrix m;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[i][j] = matrix[i][j] + x[i][j];
		}
	}
	return m;
}