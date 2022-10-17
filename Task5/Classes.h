#pragma once
#include <iostream>
#include <string>
#include <limits.h>

using namespace std;
class Matrix
{
private:
	double** MatrixElements;
	size_t Columns;
	size_t Lines;
public:
	Matrix();
	Matrix(const double** AnotherMatrix, const size_t AnotherMatrixLines, const size_t AnotherMatrixColumns);
	Matrix(const Matrix& AnotherMatrix);
	Matrix(Matrix&& AnotherMatrix);
	Matrix(const int Number);
	Matrix(const char* AnotherMatrix);
	~Matrix();
	Matrix& operator=(const Matrix& AnotherMatrix);
	Matrix& operator=(Matrix&& AnotherMatrix);
	void ShowMatrix() const;
	void ConvertMatrixToString(string& Str) const;
	const double** GetMatrix() const;
	void SetMatrixElem(const double Elem, const size_t LinesPosition, const size_t ColumnsPosition);
	void SetMatrix(double** Matr);
	const size_t GetLines() const;
	void SetLines(const int Number);
	const size_t GetColumns() const;
	void SetColumns(const int Number);

	friend const Matrix operator+ (const Matrix& Left, const Matrix& Right);
	friend const Matrix operator+ (const Matrix& Left, const int Number);
	friend const Matrix operator+ (const Matrix& Left, const char* Str);
	friend const Matrix operator- (const Matrix& Left, const Matrix& Right);
	friend const Matrix operator- (const Matrix& Left, const int Number);
	friend const Matrix operator- (const Matrix& Left, const char* Str);
	friend const Matrix operator* (const Matrix& Left, const Matrix& Right);
	friend const Matrix operator* (const Matrix& Left, const int Number);
	friend const Matrix operator* (const Matrix& Left, const char* Str);
	friend const Matrix operator/ (const Matrix& Left, const Matrix& Right);
	friend const Matrix operator/ (const Matrix& Left, const int Number);
	friend const Matrix operator/ (const Matrix& Left, const char* Str);

	const Matrix& operator+=(const Matrix& AnotherMatrix);
	const Matrix& operator+=(const int Number);
	const Matrix& operator-=(const Matrix& AnotherMatrix);
	const Matrix& operator-=(const int Number);
	const Matrix& operator*=(const Matrix& AnotherMatrix);
	const Matrix& operator*=(const int Number);
	const Matrix& operator/=(const Matrix& AnotherMatrix);
	const Matrix& operator/=(const int Number);

	friend const bool operator<(const Matrix& Left, const Matrix& Right);
	friend const bool operator>(const Matrix& Left, const Matrix& Right);
	friend const bool operator>=(const Matrix& Left, const Matrix& Right);
	friend const bool operator<=(const Matrix& Left, const Matrix& Right);
	friend const bool operator==(const Matrix& Left, const Matrix& Right);
	friend const bool operator!=(const Matrix& Left, const Matrix& Right);

	void MatrixTransponation();
};

const double FindDeterminant(const Matrix& M);

class BaseException 
{
protected:
	string TextOfMessage;
public:
	virtual const string& GetMessage() const = 0;
};

class ArithmeticalExceptions : public BaseException
{
public:
	ArithmeticalExceptions();
	ArithmeticalExceptions(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class DivisionByZero final : public ArithmeticalExceptions
{
public:
	DivisionByZero();
	DivisionByZero(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class MatricesDoNotMatch final : public ArithmeticalExceptions 
{
public:
	MatricesDoNotMatch();
	MatricesDoNotMatch(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class DeterminantWasEqualToZero final : public ArithmeticalExceptions
{
public: 
	DeterminantWasEqualToZero();
	DeterminantWasEqualToZero(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class MatricesCanNotBeCompared final : public ArithmeticalExceptions 
{
public:
	MatricesCanNotBeCompared();
	MatricesCanNotBeCompared(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class ConversionExceptions : public BaseException
{
public:
	ConversionExceptions();
	ConversionExceptions(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class CharacterIsNotANumber : public ConversionExceptions
{
public:
	CharacterIsNotANumber();
	CharacterIsNotANumber(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class OverflowExceptions : public BaseException 
{
public:
	OverflowExceptions();
	OverflowExceptions(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class OverflowWhenAddingMatrices final : public OverflowExceptions 
{
public:
	OverflowWhenAddingMatrices();
	OverflowWhenAddingMatrices(const string& ErrorText);
	virtual const string& GetMessage() const;
};

class OverflowWhenSubtractingMatrices final : public OverflowExceptions 
{
public:
	OverflowWhenSubtractingMatrices();
	OverflowWhenSubtractingMatrices(const string& ErrorText);
	virtual const string& GetMessage() const;
};