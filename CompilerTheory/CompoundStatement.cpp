#include "stdafx.h"
#include "CompoundStatement.h"

FirstTask::CCompoundStatement::CCompoundStatement(std::shared_ptr<INode> left, 
	std::shared_ptr<INode> right) : leftChild(left), rightChild(right)
{	
}

FirstTask::CCompoundStatement::~CCompoundStatement()
{
}
