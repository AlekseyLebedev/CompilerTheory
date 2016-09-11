#include "stdafx.h"
#include "OperationExpression.h"

FirstTask::COpExp::COpExp(std::shared_ptr<IExpression> left, std::shared_ptr<IExpression> right, TOperationType type) :
	leftOperand(left), rightOperand(right), operation(type)
{
}

FirstTask::COpExp::~COpExp()
{
}

std::shared_ptr<FirstTask::IExpression> FirstTask::COpExp::GetLeftOperand() const
{
	return leftOperand;
}

std::shared_ptr<FirstTask::IExpression> FirstTask::COpExp::GetRightOperand() const
{
	return rightOperand;
}

FirstTask::COpExp::TOperationType FirstTask::COpExp::GetOperationType() const
{
	return operation;
}
