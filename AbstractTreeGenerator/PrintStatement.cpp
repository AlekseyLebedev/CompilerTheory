#include "stdafx.h"
#include "PrintStatement.h"

FirstTask::CPrintStatement::CPrintStatement(std::shared_ptr<IExpression>
	_expression) : expression(_expression) {

}

FirstTask::CPrintStatement::~CPrintStatement()
{
}

std::shared_ptr<FirstTask::IExpression> FirstTask::CPrintStatement::GetExpression() const {
	return expression;
}

void FirstTask::CPrintStatement::Accept(IVisitor* v) {
	v->Visit(this);
}
