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
	try
	{
		double Determinant = FindDeterminant(M);
		if (!Determinant) throw DeterminantWasEqualToZero("Determinant of this matrix was equal to 0");
	}
	catch (const DeterminantWasEqualToZero& Ex)
	{
		cout << Ex.GetMessage() << endl;
	}
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
	Matrix Result;
	try
	{
		Result = M * OneMoreMatrix;
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
	}
	//MatricesCanNotBeCompared Exception
	try
	{
		bool BooleanResult = M == OneMoreMatrix;
	}
	catch(const MatricesCanNotBeCompared& Ex)
	{
		cout << Ex.GetMessage() << endl;
	}
	//OverflowWhenAddingMatrices Exception
	try
	{
		Result = M + 123123123123;
	}
	catch (const OverflowWhenAddingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
	}
	return 0;
}