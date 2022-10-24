#pragma once
#include <iostream>
#include <string>

using namespace std;
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