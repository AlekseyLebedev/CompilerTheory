#include "stdafx.h"
#include "OpExp.h"

FirstTask::COpExp::COpExp(std::shared_ptr<IExp> left, std::shared_ptr<IExp> right, TOperationType type) :
	leftOperand(left), rightOperand(right), operation(type)
{
}

FirstTask::COpExp::~COpExp()
{
}

std::shared_ptr<FirstTask::IExp> FirstTask::COpExp::GetLeftOperand() const
{
	return leftOperand;
}

std::shared_ptr<FirstTask::IExp> FirstTask::COpExp::GetRightOperand() const
{
	return rightOperand;
}

FirstTask::COpExp::TOperationType FirstTask::COpExp::GetOperationType() const
{
	return operation;
}
