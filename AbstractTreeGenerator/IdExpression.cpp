#include "IdExpression.h"
#include <string>

FirstTask::CIdExpression::CIdExpression(std::string theName ) : name( theName )
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


