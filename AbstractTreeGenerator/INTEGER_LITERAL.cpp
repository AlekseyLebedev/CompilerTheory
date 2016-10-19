#include "INTEGER_LITERAL.h"

FirstTask::CINTEGER_LITERAL::CINTEGER_LITERAL(int theValue) : value(theValue)
{
}

FirstTask::CINTEGER_LITERAL::CINTEGER_LITERAL(std::string theStringValue) : stringValue(theStringValue)
{
}


FirstTask::CINTEGER_LITERAL::~CINTEGER_LITERAL()
{
}

int FirstTask::CINTEGER_LITERAL::GetValue() const {
	return value;
}

std::string FirstTask::CINTEGER_LITERAL::GetStringValue() const {
	return stringValue;
}