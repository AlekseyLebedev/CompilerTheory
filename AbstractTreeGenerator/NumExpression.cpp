#include "NumExpression.h"
#include "INTEGER_LITERAL.h"

FirstTask::CNumExpression::CNumExpression(std::shared_ptr<FirstTask::CINTEGER_LITERAL> theValue) :
	value(theValue)
{
}

FirstTask::CNumExpression::~CNumExpression()
{
}

std::shared_ptr<FirstTask::CINTEGER_LITERAL> FirstTask::CNumExpression::GetValue() const {
	return value;
}

void FirstTask::CNumExpression::Accept(IVisitor* v) {
	v->Visit(this);
}