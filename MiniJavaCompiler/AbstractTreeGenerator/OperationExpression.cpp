#include "OperationExpression.h"
#include <memory>

AbstractTreeGenerator::COperationExpression::COperationExpression(IExpression* left, IExpression* right, TOperationType type) :
	leftOperand(left), rightOperand(right), operation(type)
{
}

AbstractTreeGenerator::COperationExpression::~COperationExpression()
{
}

std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::COperationExpression::GetLeftOperand() const
{
	return leftOperand;
}

std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::COperationExpression::GetRightOperand() const
{
	return rightOperand;
}

AbstractTreeGenerator::COperationExpression::TOperationType AbstractTreeGenerator::COperationExpression::GetOperationType() const
{
	return operation;
}

void AbstractTreeGenerator::COperationExpression::Accept(IVisitor* v) {
	v->visit(this);
}


