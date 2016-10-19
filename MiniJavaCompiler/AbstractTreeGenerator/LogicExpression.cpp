#include "LogicExpression.h"

AbstractTreeGenerator::CLogicExpression::CLogicExpression(std::shared_ptr<CBOOL_LITERAL> theValue) :
	value(theValue)
{
}

AbstractTreeGenerator::CLogicExpression::~CLogicExpression()
{
}