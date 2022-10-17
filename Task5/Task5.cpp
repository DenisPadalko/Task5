#include "Classes.h"

int main()
{
	//DeterminantWasEqualToZero Exception
	Matrix M;
	int Lines = 3, Columns = 3;
	double** Array = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		Array[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			Array[i][j] = (i + 1) * (j + 1);
		}
	}
	Matrix AnotherMatrix((const double**)Array, Lines, Columns);
	Matrix Result = M / AnotherMatrix;
	for (int i = 0; i < Lines; ++i) 
	{
		delete[] Array[i];
	}
	delete[] Array;
	//MatricesDoNotMatch Exception
	Lines = 2, Columns = 3;
	Array = new double* [Lines];
	for (int i = 0; i < Lines; ++i)
	{
		Array[i] = new double[Columns];
	}
	for (int i = 0; i < Lines; ++i)
	{
		for (int j = 0; j < Columns; ++j)
		{
			Array[i][j] = (i + 1) * (j + 1);
		}
	}
	Matrix OneMoreMatrix((const double**)Array, Lines, Columns);
	Result = M / OneMoreMatrix;
	//TheDivisorWasEqualToZero Exception
	Result = M / 0;
	//MatricesCanNotBeCompared Exception
	bool BooleanResult = M == OneMoreMatrix;
	//OverflowWhenAddingMatrices Exception
	Result = M + 123123123123;
	return 0;
}