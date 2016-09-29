#include "NumExpression.h"

FirstTask::CNumExpression::CNumExpression(int _value) : value(_value)
{
}

FirstTask::CNumExpression::~CNumExpression()
{
}

int FirstTask::CNumExpression::GetValue() const {
	return value;
}

void FirstTask::CNumExpression::Accept(IVisitor* v) {
	v->Visit(this);
}