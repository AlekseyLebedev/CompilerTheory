#include "CompoundStatement.h"
#include <memory>

AbstractTreeGenerator::CCompoundStatement::CCompoundStatement(std::shared_ptr<INode> left, 
	std::shared_ptr<INode> right) : leftChild(left), rightChild(right)
{	
}

AbstractTreeGenerator::CCompoundStatement::CCompoundStatement( std::shared_ptr<CStatementList> theStatementList ) :
	statementList( theStatementList )
{
}

AbstractTreeGenerator::CCompoundStatement::~CCompoundStatement()
{
}

std::shared_ptr<AbstractTreeGenerator::INode> AbstractTreeGenerator::CCompoundStatement::
	GetLeftChild() const {
	return leftChild;
}

std::shared_ptr<AbstractTreeGenerator::INode> AbstractTreeGenerator::CCompoundStatement::
	GetRightChild() const {
	return rightChild;
}

void AbstractTreeGenerator::CCompoundStatement::Accept(IVisitor* v) {
	v->Visit(this);
}

