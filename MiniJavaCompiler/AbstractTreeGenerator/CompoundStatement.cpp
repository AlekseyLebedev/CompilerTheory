#include "CompoundStatement.h"
#include <memory>

AbstractTreeGenerator::CCompoundStatement::CCompoundStatement(INode* left, 
	INode* right) : leftChild(left), rightChild(right)
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
	v->visit(this);
}

const std::shared_ptr<AbstractTreeGenerator::INode> AbstractTreeGenerator::CCompoundStatement::GetLeftChild,() const
{
	 return leftChild,;
}

const std::shared_ptr<AbstractTreeGenerator::CStatementList> AbstractTreeGenerator::CCompoundStatement::GetStatementList() const
{
	 return statementList;
}

