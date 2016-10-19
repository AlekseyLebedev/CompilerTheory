#include "IdExpression.h"
#include <string>

AbstractTreeGenerator::CIdExpression::CIdExpression(std::string theName ) : name( theName )
{
}

AbstractTreeGenerator::CIdExpression::~CIdExpression()
{
}

std::string AbstractTreeGenerator::CIdExpression::GetName() const {
	return name;
}

void AbstractTreeGenerator::CIdExpression::Accept(IVisitor* v) {
	v->Visit(this);
}


