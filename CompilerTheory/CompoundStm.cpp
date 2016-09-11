#include "stdafx.h"
#include "CompoundStm.h"

FirstTask::CompoundStm::CompoundStm(std::shared_ptr<INode> left, 
	std::shared_ptr<INode> right) : leftChild(left), rightChild(right)
{	
}

FirstTask::CompoundStm::~CompoundStm()
{
}
