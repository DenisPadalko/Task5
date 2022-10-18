#include "Exceptions.h"

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