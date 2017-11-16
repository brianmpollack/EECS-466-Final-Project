#include "FourMatrix.h"



FourMatrix::FourMatrix()
{
}


FourMatrix::~FourMatrix()
{
}

double* FourMatrix::operator[](int i)
{
	return this->matrix[i];
}

FourMatrix FourMatrix::operator + (FourMatrix x) const
{
	FourMatrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = matrix[i][j] + x[i][j];
		}
	}
	return m;
}

FourMatrix FourMatrix::operator * (const double d) const
{
	FourMatrix res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.matrix[i][j] = this->matrix[i][j] * d;
		}
	}
	return res;
}

Vector4 FourMatrix::operator * (Vector4 v) const
{
	Vector4 res(0, 0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res[i] += this->matrix[i][j] * v[j];
		}
	}
	return res;
}

FourMatrix FourMatrix::inverse() const
{
	//Adapted from: https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
	FourMatrix res = FourMatrix();

	res[0][0] = matrix[1][1]  * matrix[2][2] * matrix[3][3] - 
             matrix[1][1]  * matrix[2][3] * matrix[3][2] - 
             matrix[2][1]  * matrix[1][2]  * matrix[3][3] + 
             matrix[2][1]  * matrix[1][3]  * matrix[3][2] +
             matrix[3][1] * matrix[1][2]  * matrix[2][3] - 
             matrix[3][1] * matrix[1][3]  * matrix[2][2];

    res[1][0] = -matrix[1][0]  * matrix[2][2] * matrix[3][3] + 
              matrix[1][0]  * matrix[2][3] * matrix[3][2] + 
              matrix[2][0]  * matrix[1][2]  * matrix[3][3] - 
              matrix[2][0]  * matrix[1][3]  * matrix[3][2] - 
              matrix[3][0] * matrix[1][2]  * matrix[2][3] + 
              matrix[3][0] * matrix[1][3]  * matrix[2][2];

    res[2][0] = matrix[1][0]  * matrix[2][1] * matrix[3][3] - 
             matrix[1][0]  * matrix[2][3] * matrix[3][1] - 
             matrix[2][0]  * matrix[1][1] * matrix[3][3] + 
             matrix[2][0]  * matrix[1][3] * matrix[3][1] + 
             matrix[3][0] * matrix[1][1] * matrix[2][3] - 
             matrix[3][0] * matrix[1][3] * matrix[2][1];

    res[3][0] = -matrix[1][0]  * matrix[2][1] * matrix[3][2] + 
               matrix[1][0]  * matrix[2][2] * matrix[3][1] +
               matrix[2][0]  * matrix[1][1] * matrix[3][2] - 
               matrix[2][0]  * matrix[1][2] * matrix[3][1] - 
               matrix[3][0] * matrix[1][1] * matrix[2][2] + 
               matrix[3][0] * matrix[1][2] * matrix[2][1];

    res[0][1] = -matrix[0][1]  * matrix[2][2] * matrix[3][3] + 
              matrix[0][1]  * matrix[2][3] * matrix[3][2] + 
              matrix[2][1]  * matrix[0][2] * matrix[3][3] - 
              matrix[2][1]  * matrix[0][3] * matrix[3][2] - 
              matrix[3][1] * matrix[0][2] * matrix[2][3] + 
              matrix[3][1] * matrix[0][3] * matrix[2][2];

    res[1][1] = matrix[0][0]  * matrix[2][2] * matrix[3][3] - 
             matrix[0][0]  * matrix[2][3] * matrix[3][2] - 
             matrix[2][0]  * matrix[0][2] * matrix[3][3] + 
             matrix[2][0]  * matrix[0][3] * matrix[3][2] + 
             matrix[3][0] * matrix[0][2] * matrix[2][3] - 
             matrix[3][0] * matrix[0][3] * matrix[2][2];

    res[2][1] = -matrix[0][0]  * matrix[2][1] * matrix[3][3] + 
              matrix[0][0]  * matrix[2][3] * matrix[3][1] + 
              matrix[2][0]  * matrix[0][1] * matrix[3][3] - 
              matrix[2][0]  * matrix[0][3] * matrix[3][1] - 
              matrix[3][0] * matrix[0][1] * matrix[2][3] + 
              matrix[3][0] * matrix[0][3] * matrix[2][1];

    res[3][1] = matrix[0][0]  * matrix[2][1] * matrix[3][2] - 
              matrix[0][0]  * matrix[2][2] * matrix[3][1] - 
              matrix[2][0]  * matrix[0][1] * matrix[3][2] + 
              matrix[2][0]  * matrix[0][2] * matrix[3][1] + 
              matrix[3][0] * matrix[0][1] * matrix[2][2] - 
              matrix[3][0] * matrix[0][2] * matrix[2][1];

    res[0][2] = matrix[0][1]  * matrix[1][2] * matrix[3][3] - 
             matrix[0][1]  * matrix[1][3] * matrix[3][2] - 
             matrix[1][1]  * matrix[0][2] * matrix[3][3] + 
             matrix[1][1]  * matrix[0][3] * matrix[3][2] + 
             matrix[3][1] * matrix[0][2] * matrix[1][3] - 
             matrix[3][1] * matrix[0][3] * matrix[1][2];

    res[1][2] = -matrix[0][0]  * matrix[1][2] * matrix[3][3] + 
              matrix[0][0]  * matrix[1][3] * matrix[3][2] + 
              matrix[1][0]  * matrix[0][2] * matrix[3][3] - 
              matrix[1][0]  * matrix[0][3] * matrix[3][2] - 
              matrix[3][0] * matrix[0][2] * matrix[1][3] + 
              matrix[3][0] * matrix[0][3] * matrix[1][2];

    res[2][2] = matrix[0][0]  * matrix[1][1] * matrix[3][3] - 
              matrix[0][0]  * matrix[1][3] * matrix[3][1] - 
              matrix[1][0]  * matrix[0][1] * matrix[3][3] + 
              matrix[1][0]  * matrix[0][3] * matrix[3][1] + 
              matrix[3][0] * matrix[0][1] * matrix[1][3] - 
              matrix[3][0] * matrix[0][3] * matrix[1][1];

    res[3][2] = -matrix[0][0]  * matrix[1][1] * matrix[3][2] + 
               matrix[0][0]  * matrix[1][2] * matrix[3][1] + 
               matrix[1][0]  * matrix[0][1] * matrix[3][2] - 
               matrix[1][0]  * matrix[0][2] * matrix[3][1] - 
               matrix[3][0] * matrix[0][1] * matrix[1][2] + 
               matrix[3][0] * matrix[0][2] * matrix[1][1];

    res[0][3] = -matrix[0][1] * matrix[1][2] * matrix[2][3] + 
              matrix[0][1] * matrix[1][3] * matrix[2][2] + 
              matrix[1][1] * matrix[0][2] * matrix[2][3] - 
              matrix[1][1] * matrix[0][3] * matrix[2][2] - 
              matrix[2][1] * matrix[0][2] * matrix[1][3] + 
              matrix[2][1] * matrix[0][3] * matrix[1][2];

    res[1][3] = matrix[0][0] * matrix[1][2] * matrix[2][3] - 
             matrix[0][0] * matrix[1][3] * matrix[2][2] - 
             matrix[1][0] * matrix[0][2] * matrix[2][3] + 
             matrix[1][0] * matrix[0][3] * matrix[2][2] + 
             matrix[2][0] * matrix[0][2] * matrix[1][3] - 
             matrix[2][0] * matrix[0][3] * matrix[1][2];

    res[2][3] = -matrix[0][0] * matrix[1][1] * matrix[2][3] + 
               matrix[0][0] * matrix[1][3] * matrix[2][1] + 
               matrix[1][0] * matrix[0][1] * matrix[2][3] - 
               matrix[1][0] * matrix[0][3] * matrix[2][1] - 
               matrix[2][0] * matrix[0][1] * matrix[1][3] + 
               matrix[2][0] * matrix[0][3] * matrix[1][1];

    res[3][3] = matrix[0][0] * matrix[1][1] * matrix[2][2] - 
              matrix[0][0] * matrix[1][2] * matrix[2][1] - 
              matrix[1][0] * matrix[0][1] * matrix[2][2] + 
              matrix[1][0] * matrix[0][2] * matrix[2][1] + 
              matrix[2][0] * matrix[0][1] * matrix[1][2] - 
              matrix[2][0] * matrix[0][2] * matrix[1][1];


	double det = matrix[0][0] * res[0][0] + matrix[0][1] * res[1][0] + matrix[0][2] * res[2][0] + matrix[0][3] * res[3][0];

	if (abs(det) < 0.000001)
	{
		throw std::domain_error("Determinant is 0.");
	}
		

	det = 1.0 / det;

	return res * det;

}

void FourMatrix::reset()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = 0.0;
		}
	}
}
