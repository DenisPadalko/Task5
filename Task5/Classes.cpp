#include "Classes.h"

Matrix::Matrix() : Lines(3), Columns(3)
{
	MatrixElements = new double* [Lines];
	for (size_t i = 0; i < Lines; ++i) 
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = j + 1;
		}
	}
};

Matrix::Matrix(const double** AnotherMatrix, const size_t AnotherMatrixLines, const size_t AnotherMatrixColumns) : Lines(AnotherMatrixLines), Columns(AnotherMatrixColumns)
{
	MatrixElements = new double* [Lines];
	for (size_t i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix[i][j];
		}
	}
};

Matrix::Matrix(const Matrix& AnotherMatrix) : Lines(AnotherMatrix.Lines), Columns(AnotherMatrix.Columns)
{
	MatrixElements = new double* [Lines];
	for (size_t i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix.MatrixElements[i][j];
		}
	}
};

Matrix::Matrix(Matrix&& AnotherMatrix) : Lines(AnotherMatrix.Lines), Columns(AnotherMatrix.Columns), MatrixElements(AnotherMatrix.MatrixElements)
{
	for (size_t i = 0; i < AnotherMatrix.Lines; ++i)
	{
		delete[] AnotherMatrix.MatrixElements[i];
	}
	delete[] AnotherMatrix.MatrixElements;
};

Matrix::Matrix(const int Number) : Lines(1), Columns(1)
{
	MatrixElements = new double* [1];
	MatrixElements[0] = new double[1];
	MatrixElements[0][0] = Number;
};

Matrix::Matrix(const char* AnotherMatrix) : Lines(0), Columns(1)
{
	size_t i = 0, j = 0;
	size_t Col = 1;
	while (AnotherMatrix[i] != '\0')
	{
		if (AnotherMatrix[i] == ',')
		{
			Col += 1;
		}
		else if (AnotherMatrix[i] == ';')
		{
			Lines += 1;
			Columns = Col;
			Col = 1;
		}
		i++;
	}
	MatrixElements = new double* [Lines];
	for (i = 0; i < Lines; ++i)
	{
		MatrixElements[i] = new double[Columns];
	}
	const char s[6] = "[];, ";
	char* Number;
	char* NextNumber;
	Number = strtok_s((char*)AnotherMatrix, s, &NextNumber);
	for (i = 0; i < Lines; ++i)
	{
		for (j = 0; j < Columns; j++)
		{
			MatrixElements[i][j] = strtod(Number, NULL);
			Number = strtok_s(NULL, s, &NextNumber);
		}
	}
};

Matrix::~Matrix()
{
	if (MatrixElements != nullptr)
	{
		for (size_t i = 0; i < Lines; ++i)
		{
			delete[] MatrixElements[i];
		}
		delete[] MatrixElements;
	}
};

Matrix& Matrix::operator=(const Matrix& AnotherMatrix)
{
	if (&AnotherMatrix == this) return *this;
	for (size_t i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;

	Columns = AnotherMatrix.Columns;
	Lines = AnotherMatrix.Lines;
	MatrixElements = new double* [Lines];
	for (size_t i = 0; i < Lines; i++)
	{
		MatrixElements[i] = new double[Columns];
	}
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] = AnotherMatrix.MatrixElements[i][j];
		}
	}

	return *this;
};

Matrix& Matrix::operator=(Matrix&& AnotherMatrix)
{
	if (&AnotherMatrix == this) return *this;

	for (size_t i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;

	Lines = AnotherMatrix.Lines;
	Columns = AnotherMatrix.Columns;
	MatrixElements = AnotherMatrix.MatrixElements;
	for (size_t i = 0; i < AnotherMatrix.Lines; ++i)
	{
		delete[] AnotherMatrix.MatrixElements[i];
	}
	delete[] AnotherMatrix.MatrixElements;

	return *this;
};

void Matrix::ShowMatrix() const
{
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			cout << MatrixElements[i][j] << " ";
		}
		cout << endl;
	}
};

void Matrix::ConvertMatrixToString(string& Str) const
{
	Str += '[';
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			Str += to_string(MatrixElements[i][j]);
			if (j < (Columns - 1))
			{
				Str += ", ";
			}
		}
		Str += "; ";
	}
	Str += ']';
};

const double** Matrix::GetMatrix() const
{
	return (const double**)MatrixElements;
};

void Matrix::SetMatrixElem(const double Elem, const size_t LinesPosition, const size_t ColumnsPosition)
{
	MatrixElements[LinesPosition][ColumnsPosition] = Elem;
};

void Matrix::SetMatrix(double** Matr)
{
	for (size_t i = 0; i < Lines; ++i)
	{
		delete[] MatrixElements[i];
	}
	delete[] MatrixElements;
	MatrixElements = Matr;
};

const size_t Matrix::GetLines() const
{
	return Lines;
};

void Matrix::SetLines(const int Number)
{
	Lines = Number;
};

const size_t Matrix::GetColumns() const
{
	return Columns;
};

void Matrix::SetColumns(const int Number)
{
	Columns = Number;
};

const Matrix operator+ (const Matrix& Left, const Matrix& Right)
{
	try
	{
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesDoNotMatch("Failed to add matrices");
		}
		int Lines = Left.Lines;
		int Columns = Left.Columns;
		double** MatrixElements = new double* [Lines];
		for (size_t i = 0; i < Lines; ++i)
		{
			MatrixElements[i] = new double[Columns];
		}
		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < Columns; ++j)
			{
				if (((Right.MatrixElements[i][j] > 0) && (Left.MatrixElements[i][j] > (DBL_MAX - Right.MatrixElements[i][j]))) ||
					((Right.MatrixElements[i][j] < 0) && (Left.MatrixElements[i][j] < (DBL_MIN - Right.MatrixElements[i][j]))))
				{
					throw OverflowWhenAddingMatrices("An overflow occurred while adding matrices");
				}
				else
				{
					MatrixElements[i][j] = Left.MatrixElements[i][j] + Right.MatrixElements[i][j];
				};
			}
		}
		return Matrix((const double**)MatrixElements, Lines, Columns);
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
	catch (const OverflowWhenAddingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix operator+ (const Matrix& Left, const int Number)
{
	try
	{
		double** MatrixElements = new double* [Left.Lines];
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			MatrixElements[i] = new double[Left.Columns];
		}
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (i == j)
				{
					if (((Number > 0) && (Left.MatrixElements[i][j] > (DBL_MAX - Number))) ||
						((Number < 0) && (Left.MatrixElements[i][j] < (DBL_MIN - Number))))
					{
						throw OverflowWhenAddingMatrices("An overflow occurred while adding matrices");
					}
					else MatrixElements[i][j] = Left.MatrixElements[i][j] + Number;
				}
				else MatrixElements[i][j] = Left.MatrixElements[i][j];
			}
		}
		return Matrix((const double**)MatrixElements, Left.Lines, Left.Columns);
	}
	catch (const OverflowWhenAddingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix operator+ (const Matrix& Left, const char* Str)
{
	return Left + atoi(Str);
};

const Matrix operator- (const Matrix& Left, const Matrix& Right)
{
	try
	{
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesDoNotMatch("Failed to subtract matrices");
		}
		double** MatrixElements = new double* [Left.Lines];
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			MatrixElements[i] = new double[Left.Columns];
		}
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (((Right.MatrixElements[i][j] > 0) && (Left.MatrixElements[i][j] < (DBL_MIN + Right.MatrixElements[i][j]))) ||
					((Right.MatrixElements[i][j] < 0) && (Left.MatrixElements[i][j] > (DBL_MAX + Right.MatrixElements[i][j]))))
				{
					throw OverflowWhenSubtractingMatrices("An overflow occurred while subtracting matrices");
				}
				else
				{
					MatrixElements[i][j] = Left.MatrixElements[i][j] - Right.MatrixElements[i][j];
				};
			}
		}
		return Matrix((const double**)MatrixElements, Left.Lines, Left.Columns);
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
	catch (const OverflowWhenSubtractingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix operator- (const Matrix& Left, const int Number)
{
	try
	{
		double** MatrixElements = new double* [Left.Lines];
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			MatrixElements[i] = new double[Left.Columns];
		}
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (i == j)
				{
					if (((Number > 0) && (Left.MatrixElements[i][j] < (DBL_MIN + Number))) ||
						((Number < 0) && (Left.MatrixElements[i][j] > (DBL_MAX + Number))))
					{
						throw OverflowWhenSubtractingMatrices("An overflow occurred while subtracting matrices");
					}
					else MatrixElements[i][j] = Left.MatrixElements[i][j] - Number;
				}
				else MatrixElements[i][j] = Left.MatrixElements[i][j];
			}
		}
		return Matrix((const double**)MatrixElements, Left.Lines, Left.Columns);
	}
	catch (const OverflowWhenSubtractingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix operator- (const Matrix& Left, const char* Str)
{
	return Left - atoi(Str);
};

const Matrix operator* (const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (Left.Columns != Right.Lines)
		{
			throw MatricesDoNotMatch("Failed to multiply matrices");
		}
		double** MatrixElements = new double* [Left.Lines];
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			MatrixElements[i] = new double[Left.Columns];
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				MatrixElements[i][j] = 0;
				for (size_t k = 0; k < Left.Columns; ++k)
				{
					MatrixElements[i][j] += Left.MatrixElements[i][k] * Right.MatrixElements[k][j];
				}
				if (MatrixElements[i][j] < 0.000000001)
				{
					MatrixElements[i][j] = 0;
				}
			}
		}
		return Matrix((const double**)MatrixElements, Left.Lines, Left.Columns);
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix operator* (const Matrix& Left, const int Number)
{
	double** MatrixElements = new double* [Left.Lines];
	for (size_t i = 0; i < Left.Lines; ++i)
	{
		MatrixElements[i] = new double[Left.Columns];
	}
	for (size_t i = 0; i < Left.Lines; ++i)
	{
		for (size_t j = 0; j < Left.Columns; ++j)
		{
			MatrixElements[i][j] = Left.MatrixElements[i][j] * Number;
		}
	}
	return Matrix((const double**)MatrixElements, Left.Lines, Left.Columns);
};

const Matrix operator* (const Matrix& Left, const char* Str)
{
	return Left * atoi(Str);
};

void GetMatr(const double** Mas, double** P, const int i, const int j, const int m)
{
	int di, dj;
	di = 0;
	for (size_t ki = 0; ki < m - 1; ++ki)
	{
		if (ki == i) di = 1;
		dj = 0;
		for (size_t kj = 0; kj < m - 1; ++kj)
		{
			if (kj == j) dj = 1;
			P[ki][kj] = Mas[ki + di][kj + dj];
		}
	}
}

const double FindDeterminant(const Matrix& M)
{
	double Determinant = 0;
	int k, n;
	double** P;
	P = new double* [M.GetLines()];
	for (int i = 0; i < M.GetLines(); ++i) P[i] = new double[M.GetLines()];
	k = 1;
	n = M.GetLines() - 1;
	if (M.GetLines() == 1)
	{
		return M.GetMatrix()[0][0];
	}
	if (M.GetLines() == 2)
	{
		Determinant = M.GetMatrix()[0][0] * M.GetMatrix()[1][1] - (M.GetMatrix()[1][0] * M.GetMatrix()[0][1]);
		return Determinant;
	}
	if (M.GetLines() > 2)
	{
		for (size_t i = 0; i < M.GetLines(); ++i)
		{
			GetMatr(M.GetMatrix(), P, i, 0, M.GetLines());
			Matrix TempMatrix((const double**)(P), n, n);
			Determinant = Determinant + k * M.GetMatrix()[i][0] * FindDeterminant(TempMatrix);
			k = -k;
		}
	}
	return Determinant;
}

int GetMinor(const double** A, double** B, int x, int y, int size)
{
	int XCount = 0, YCount = 0;
	for (size_t i = 0; i < size; ++i)
	{
		if (i != x)
		{
			YCount = 0;
			for (size_t j = 0; j < size; ++j)
			{
				if (j != y)
				{
					B[XCount][YCount] = A[i][j];
					YCount++;
				}
			}
			XCount++;
		}
	}
	return 0;
}

double FindArrayDeterminant(const double** A, const int Size)
{
	if (Size == 1)
	{
		return A[0][0];
	}
	else
	{
		int Det = 0;
		double** Minor = new double* [Size - 1];
		for (size_t i = 0; i < Size; ++i)
		{
			Minor[i] = new double[Size - 1];
		}
		for (size_t i = 0; i < Size; ++i)
		{
			GetMinor(A, Minor, 0, i, Size);
			Det += pow(-1, i) * A[0][i] * FindArrayDeterminant((const double**)Minor, Size - 1);
		}
		return Det;
	}
}

void FindAlgDop(const double** A, const int Size, double** B)
{
	int Det = FindArrayDeterminant(A, Size);
	if (Det > 0) Det = -1;
	else Det = 1;
	double** Minor = new double* [Size - 1];
	for (size_t i = 0; i < Size - 1; ++i)
	{
		Minor[i] = new double[Size - 1];
	}
	for (size_t j = 0; j < Size; ++j)
	{
		for (size_t i = 0; i < Size; ++i)
		{
			GetMinor(A, Minor, j, i, Size);
			if ((i + j) % 2 == 0)
				B[j][i] = -Det * FindArrayDeterminant((const double**)Minor, Size - 1);
			else
				B[j][i] = Det * FindArrayDeterminant((const double**)Minor, Size - 1);
		}
	}
	for (size_t i = 0; i < Size - 1; ++i)
	{
		delete[] Minor[i];
	}
	delete[] Minor;
}

void Matrix::MatrixTransponation()
{
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = i; j < Columns; ++j)
		{
			swap(MatrixElements[i][j], MatrixElements[j][i]);
		}
	}
}

const Matrix operator/ (const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (Left.Columns != Right.Lines)
		{
			throw MatricesDoNotMatch("Matrices don't match. Failed to divide matrices");
		}
		if (Right.Lines != Right.Columns)
		{
			throw MatricesDoNotMatch("Second operator is not a square matrix. Failed to divide matrices");
		}
		double Determinant = FindDeterminant(Right);
		if (Determinant == 0)
		{
			throw DeterminantWasEqualToZero("Determinant was equal to 0. Failed to divide matrices");
		}
		for (size_t i = 0; i < Right.Lines; ++i)
		{
			for (size_t j = 0; j < Right.Columns; ++j)
			{
				if (Right.MatrixElements[i][j] == 0)
				{
					throw DivisionByZero("Divisor was equal to 0. Failed to divide matrices");
				}
			}
		}
		double** Result = new double* [Right.Lines];
		for (size_t i = 0; i < Right.Lines; ++i)
		{
			Result[i] = new double[Right.Columns];
		}
		FindAlgDop((const double**)Right.MatrixElements, Right.Lines, Result);
		Matrix Copy((const double**)Result, Right.Lines, Right.Columns);
		Copy.MatrixTransponation();
		for (size_t i = 0; i < Copy.Lines; ++i)
		{
			for (size_t j = 0; j < Copy.Columns; ++j)
			{
				Copy.MatrixElements[i][j] /= Determinant;
			}
		}
		for (size_t i = 0; i < Right.Lines; ++i)
		{
			delete[] Result[i];
		}
		delete[] Result;
		return Left * Copy;
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
	catch (const DeterminantWasEqualToZero& Ex) 
	{
		cout << Ex.GetMessage() << endl; 
		return 0;
	}
	catch (const DivisionByZero& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix operator/ (const Matrix& Left, const int Number)
{
	try
	{
		if (Number == 0)
		{
			throw DivisionByZero("The divisor was equal to 0");
		}
		double** MatrixElements = new double* [Left.Lines];
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			MatrixElements[i] = new double[Left.Columns];
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				MatrixElements[i][j] = Left.MatrixElements[i][j];
			}
		}
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				MatrixElements[i][j] /= Number;
			}
		}
		return Matrix((const double**)MatrixElements, Left.Lines, Left.Columns);
	}
	catch (const DivisionByZero& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix operator/ (const Matrix& Left, const char* Str)
{
	return Left + atoi(Str);
};

const Matrix& Matrix::operator+=(const Matrix& AnotherMatrix)
{
	try
	{
		if ((Lines != AnotherMatrix.Lines) || (Columns != AnotherMatrix.Columns))
		{
			throw MatricesDoNotMatch("Matrices don't match. Failed to add matrices");
		}
		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < Columns; ++j)
			{
				if (((AnotherMatrix.MatrixElements[i][j] > 0) && (MatrixElements[i][j] > (DBL_MAX - AnotherMatrix.MatrixElements[i][j]))) ||
					((AnotherMatrix.MatrixElements[i][j] < 0) && (MatrixElements[i][j] < (DBL_MIN - AnotherMatrix.MatrixElements[i][j]))))
				{
					throw OverflowWhenAddingMatrices("An overflow occurred while adding matrices");
				}
				else MatrixElements[i][j] += AnotherMatrix.MatrixElements[i][j];
			}
		}
		return *this;
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
	catch (const OverflowWhenAddingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix& Matrix::operator+=(const int Number)
{
	try
	{
		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < Columns; ++j)
			{
				if (i == j)
				{
					if (((Number > 0) && (MatrixElements[i][j] > (DBL_MAX - Number))) ||
						((Number < 0) && (MatrixElements[i][j] < (DBL_MIN - Number))))
					{
						throw OverflowWhenAddingMatrices("An overflow occurred while adding matrices");
					}
					else MatrixElements[i][j] += Number;
				}
			}
		}
		return *this;
	}
	catch (const OverflowWhenAddingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix& Matrix::operator-=(const Matrix& AnotherMatrix)
{
	try
	{
		if ((Lines != AnotherMatrix.Lines) || (Columns != AnotherMatrix.Columns))
		{
			throw MatricesDoNotMatch("Matrices don't match. Failed to subtract matrices");
		}
		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < Columns; ++j)
			{
				if (((AnotherMatrix.MatrixElements[i][j] > 0) && (MatrixElements[i][j] < (DBL_MIN + AnotherMatrix.MatrixElements[i][j]))) ||
					((AnotherMatrix.MatrixElements[i][j] < 0) && (MatrixElements[i][j] > (DBL_MAX + AnotherMatrix.MatrixElements[i][j]))))
				{
					throw OverflowWhenSubtractingMatrices("An overflow occurred while subtracting matrices");
				}
				else MatrixElements[i][j] -= AnotherMatrix.MatrixElements[i][j];
			}
		}
		return *this;
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
	catch (const OverflowWhenSubtractingMatrices& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix& Matrix::operator-=(const int Number)
{
	try
	{
		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < Columns; ++j)
			{
				if (i == j) {
					if (((Number > 0) && (MatrixElements[i][j] < (DBL_MIN + Number))) ||
						((Number < 0) && (MatrixElements[i][j] > (DBL_MAX + Number))))
					{
						throw OverflowWhenSubtractingMatrices("An overflow occurred while subtracting matrices");
					}
					else MatrixElements[i][j] -= Number;
				}
			}
		}
		return *this;
	}
	catch (const OverflowWhenSubtractingMatrices& Ex) 
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix& Matrix::operator*=(const Matrix& AnotherMatrix)
{
	try
	{
		if (Columns != AnotherMatrix.Lines)
		{
			throw MatricesDoNotMatch("Matrices don't match. Failed to multiply matrices");
		}
		double** Temp = new double* [Lines];
		for (size_t i = 0; i < Lines; ++i)
		{
			Temp[i] = new double[Columns];
		}
		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < Columns; ++j)
			{
				Temp[i][j] = MatrixElements[i][j];
			}
		}
		for (size_t i = 0; i < Lines; ++i)
		{
			delete[] MatrixElements[i];
		}
		delete[] MatrixElements;

		MatrixElements = new double* [Lines];
		for (size_t i = 0; i < Lines; ++i)
		{
			MatrixElements[i] = new double[AnotherMatrix.Columns];
		}
		for (size_t i = 0; i < Lines; ++i)
		{
			for (size_t j = 0; j < AnotherMatrix.Columns; ++j)
			{
				MatrixElements[i][j] = 0;
				for (size_t k = 0; k < AnotherMatrix.Columns; ++k)
				{
					MatrixElements[i][j] += Temp[i][k] * AnotherMatrix.MatrixElements[k][j];
				}
			}
		}

		for (size_t i = 0; i < Lines; ++i)
		{
			delete[] Temp[i];
		}
		delete[] Temp;
		return *this;
	}
	catch (const MatricesDoNotMatch& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix& Matrix::operator*=(const int Number)
{
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] *= Number;
		}
	}
	return *this;
};

const Matrix& Matrix::operator/=(const Matrix& AnotherMatrix)
{
	try
	{
		if (Columns != AnotherMatrix.Lines)
		{
			throw MatricesDoNotMatch("Matrices don't match. Failed to divide matrices");
		}
		if (AnotherMatrix.Lines != AnotherMatrix.Columns)
		{
			throw MatricesDoNotMatch("Second operator is not a square matrix. Failed to divide matrices");
		}
		double Determinant = FindDeterminant(AnotherMatrix);
		if (Determinant == 0)
		{
			throw DeterminantWasEqualToZero("Determinant was equal to 0. Failed to divide matrices");
		}
		for (size_t i = 0; i < AnotherMatrix.Lines; ++i)
		{
			for (size_t j = 0; j < AnotherMatrix.Columns; ++j)
			{
				if (AnotherMatrix.MatrixElements[i][j] == 0)
				{
					throw DivisionByZero("Divisor was equal to 0. Failed to divide matrices");
				}
			}
		}
		double** Result = new double* [AnotherMatrix.Lines];
		for (size_t i = 0; i < AnotherMatrix.Lines; ++i)
		{
			Result[i] = new double[AnotherMatrix.Columns];
		}
		FindAlgDop((const double**)AnotherMatrix.MatrixElements, AnotherMatrix.Lines, Result);
		Matrix Copy((const double**)Result, AnotherMatrix.Lines, AnotherMatrix.Columns);
		Copy.MatrixTransponation();
		for (size_t i = 0; i < Copy.Lines; ++i)
		{
			for (size_t j = 0; j < Copy.Columns; ++j)
			{
				Copy.MatrixElements[i][j] /= Determinant;
			}
		}
		Matrix Res = *this * Copy;
		for (size_t i = 0; i < Lines; ++i)
		{
			delete[] MatrixElements[i];
		}
		for (size_t i = 0; i < Lines; ++i)
		{
			MatrixElements[i] = new double[Columns];
			for (size_t j = 0; j < Columns; ++j)
			{
				MatrixElements[i][j] = Res.MatrixElements[i][j];
			}
		}
		for (size_t i = 0; i < AnotherMatrix.Lines; ++i)
		{
			delete[] Result[i];
		}
		delete[] Result;
		return *this;
	}
	catch (const MatricesDoNotMatch& Ex) 
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
	catch (const DeterminantWasEqualToZero& Ex) 
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
	catch (const DivisionByZero& Ex) 
	{
		cout << Ex.GetMessage() << endl;
		return 0;
	}
};

const Matrix& Matrix::operator/=(const int Number)
{
	for (size_t i = 0; i < Lines; ++i)
	{
		for (size_t j = 0; j < Columns; ++j)
		{
			MatrixElements[i][j] /= Number;
		}
	}
	return *this;
};

const bool operator<(const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (&Left == &Right) return false;
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesCanNotBeCompared("Those matrices cannot be compared");
		}
		bool Result = false;
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (Left.MatrixElements[i][j] < Right.MatrixElements[i][j]) Result = true;
				else Result = false;
			}
		}
		return Result;
	}
	catch (const MatricesCanNotBeCompared& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return false;
	}
};

const bool operator>(const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (&Left == &Right) return false;
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesCanNotBeCompared("Those matrices cannot be compared");
		}
		bool Result = false;
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (Left.MatrixElements[i][j] > Right.MatrixElements[i][j]) Result = true;
				else Result = false;
			}
		}
		return Result;
	}
	catch (const MatricesCanNotBeCompared& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return false;
	}
};

const bool operator>=(const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (&Left == &Right) return true;
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesCanNotBeCompared("Those matrices cannot be compared");
		}
		bool Result = false;
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (Left.MatrixElements[i][j] >= Right.MatrixElements[i][j]) Result = true;
				else Result = false;
			}
		}
		return Result;
	}
	catch (const MatricesCanNotBeCompared& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return false;
	}
};

const bool operator<=(const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (&Left == &Right) return true;
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesCanNotBeCompared("Those matrices cannot be compared");
		}
		bool Result = false;
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (Left.MatrixElements[i][j] <= Right.MatrixElements[i][j]) Result = true;
				else Result = false;
			}
		}
		return Result;
	}
	catch (const MatricesCanNotBeCompared& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return false;
	}
};

const bool operator==(const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (&Left == &Right) return true;
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesCanNotBeCompared("Those matrices cannot be compared");
		}
		bool Result = false;
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (Left.MatrixElements[i][j] == Right.MatrixElements[i][j]) Result = true;
				else Result = false;
			}
		}
		return Result;
	}
	catch (const MatricesCanNotBeCompared& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return false;
	}
};

const bool operator!=(const Matrix& Left, const Matrix& Right)
{
	try
	{
		if (&Left == &Right) return false;
		if ((Left.Lines != Right.Lines) || (Left.Columns != Right.Columns))
		{
			throw MatricesCanNotBeCompared("Those matrices cannot be compared");
		}
		bool Result = false;
		for (size_t i = 0; i < Left.Lines; ++i)
		{
			for (size_t j = 0; j < Left.Columns; ++j)
			{
				if (Left.MatrixElements[i][j] != Right.MatrixElements[i][j]) Result = true;
				else Result = false;
			}
		}
		return Result;
	}
	catch (const MatricesCanNotBeCompared& Ex)
	{
		cout << Ex.GetMessage() << endl;
		return false;
	}
};

ArithmeticalExceptions::ArithmeticalExceptions()
{
	TextOfMessage = "Error. Arithmetical exception.";
}

ArithmeticalExceptions::ArithmeticalExceptions(const string& ErrorText) 
{
	TextOfMessage = ErrorText;
}

const string& ArithmeticalExceptions::GetMessage() const
{
	return TextOfMessage;
}

DivisionByZero::DivisionByZero() : ArithmeticalExceptions()
{}

DivisionByZero::DivisionByZero(const string& ErrorText) : ArithmeticalExceptions(ErrorText) 
{}

const string& DivisionByZero::GetMessage() const
{
	return TextOfMessage;
}

MatricesDoNotMatch::MatricesDoNotMatch() : ArithmeticalExceptions()
{}

MatricesDoNotMatch::MatricesDoNotMatch(const string& ErrorText) : ArithmeticalExceptions(ErrorText) 
{}

const string& MatricesDoNotMatch::GetMessage() const
{
	return TextOfMessage;
}

DeterminantWasEqualToZero::DeterminantWasEqualToZero() : ArithmeticalExceptions() 
{}

DeterminantWasEqualToZero::DeterminantWasEqualToZero(const string& ErrorText) : ArithmeticalExceptions(ErrorText) 
{}

const string& DeterminantWasEqualToZero::GetMessage() const
{
	return TextOfMessage;
}

MatricesCanNotBeCompared::MatricesCanNotBeCompared() : ArithmeticalExceptions() 
{}

MatricesCanNotBeCompared::MatricesCanNotBeCompared(const string& ErrorText) : ArithmeticalExceptions(ErrorText) 
{}

const string& MatricesCanNotBeCompared::GetMessage() const
{
	return TextOfMessage;
}

ConversionExceptions::ConversionExceptions() 
{
	TextOfMessage = "Error. Conversion exception.";
}

ConversionExceptions::ConversionExceptions(const string& ErrorText) 
{
	TextOfMessage = ErrorText;
}

const string& ConversionExceptions::GetMessage() const
{
	return TextOfMessage;
}

OverflowExceptions::OverflowExceptions()
{
	TextOfMessage = "Error. Overflow exception";
}

OverflowExceptions::OverflowExceptions(const string& ErrorText) 
{
	TextOfMessage = ErrorText;
}

const string& OverflowExceptions::GetMessage() const
{
	return TextOfMessage;
}

OverflowWhenAddingMatrices::OverflowWhenAddingMatrices() : OverflowExceptions() 
{}

OverflowWhenAddingMatrices::OverflowWhenAddingMatrices(const string& ErrorText) : OverflowExceptions(ErrorText) 
{}

const string& OverflowWhenAddingMatrices::GetMessage() const
{
	return TextOfMessage;
}

OverflowWhenSubtractingMatrices::OverflowWhenSubtractingMatrices() : OverflowExceptions()
{}

OverflowWhenSubtractingMatrices::OverflowWhenSubtractingMatrices(const string& ErrorText) : OverflowExceptions(ErrorText)
{}

const string& OverflowWhenSubtractingMatrices::GetMessage() const
{
	return TextOfMessage;
}