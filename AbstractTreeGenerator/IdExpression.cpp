#include "stdafx.h"
#include "IdExpression.h"


FirstTask::CIdExpression::CIdExpression(std::string _name) : name(_name)
{
}

FirstTask::CIdExpression::~CIdExpression()
{
}

std::string FirstTask::CIdExpression::GetName() const {
	return name;
}

void FirstTask::CIdExpression::Accept(IVisitor* v) {
	v->Visit(this);
}


