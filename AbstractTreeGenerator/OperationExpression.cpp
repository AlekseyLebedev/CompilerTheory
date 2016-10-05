#include "OperationExpression.h"
#include <memory>

FirstTask::COperationExpression::COperationExpression(std::shared_ptr<IExpression> left, std::shared_ptr<IExpression> right, TOperationType type) :
	leftOperand(left), rightOperand(right), operation(type)
{
}

FirstTask::COperationExpression::~COperationExpression()
{
}

std::shared_ptr<FirstTask::IExpression> FirstTask::COperationExpression::GetLeftOperand() const
{
	return leftOperand;
}

std::shared_ptr<FirstTask::IExpression> FirstTask::COperationExpression::GetRightOperand() const
{
	return rightOperand;
}

FirstTask::COperationExpression::TOperationType FirstTask::COperationExpression::GetOperationType() const
{
	return operation;
}

void FirstTask::COperationExpression::Accept(IVisitor* v) {
	v->Visit(this);
}