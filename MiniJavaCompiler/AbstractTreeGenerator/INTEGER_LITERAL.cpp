#include "INTEGER_LITERAL.h"

AbstractTreeGenerator::CINTEGER_LITERAL::CINTEGER_LITERAL(int theValue) : value(theValue)
{
}

AbstractTreeGenerator::CINTEGER_LITERAL::CINTEGER_LITERAL(std::string theStringValue) : stringValue(theStringValue)
{
}


AbstractTreeGenerator::CINTEGER_LITERAL::~CINTEGER_LITERAL()
{
}

int AbstractTreeGenerator::CINTEGER_LITERAL::GetValue() const {
	return value;
}

std::string AbstractTreeGenerator::CINTEGER_LITERAL::GetStringValue() const {
	return stringValue;
}

void AbstractTreeGenerator::CINTEGER_LITERAL::Accept( IVisitor * v)
{
	v->visit( this );
}
