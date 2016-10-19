#include "CompoundStatement.h"
#include <memory>

FirstTask::CCompoundStatement::CCompoundStatement(std::shared_ptr<INode> left, 
	std::shared_ptr<INode> right) : leftChild(left), rightChild(right)
{	
}

FirstTask::CCompoundStatement::CCompoundStatement( std::shared_ptr<CStatementList> theStatementList ) :
	statementList( theStatementList )
{
}

FirstTask::CCompoundStatement::~CCompoundStatement()
{
}

std::shared_ptr<FirstTask::INode> FirstTask::CCompoundStatement::
	GetLeftChild() const {
	return leftChild;
}

std::shared_ptr<FirstTask::INode> FirstTask::CCompoundStatement::
	GetRightChild() const {
	return rightChild;
}

void FirstTask::CCompoundStatement::Accept(IVisitor* v) {
	v->Visit(this);
}

