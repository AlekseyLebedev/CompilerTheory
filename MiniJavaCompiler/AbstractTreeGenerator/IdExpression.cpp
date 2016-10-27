#include "IdExpression.h"
#include <string>

AbstractTreeGenerator::CIdExpression::CIdExpression(std::string theName ) : name( theName )
{
}

AbstractTreeGenerator::CIdExpression::~CIdExpression()
{
}

void AbstractTreeGenerator::CIdExpression::Accept(IVisitor* v) {
	v->visit(this);
}


const std::string AbstractTreeGenerator::CIdExpression::GetName() const
{
	 return name;
}

