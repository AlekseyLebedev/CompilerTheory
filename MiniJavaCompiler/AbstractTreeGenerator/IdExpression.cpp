#include "IdExpression.h"
#include <string>

AbstractTreeGenerator::CIdExpression::CIdExpression(int theName ) : name( theName )
{
}

AbstractTreeGenerator::CIdExpression::~CIdExpression()
{
}

void AbstractTreeGenerator::CIdExpression::Accept(IVisitor* v) {
	v->visit(this);
}


const int AbstractTreeGenerator::CIdExpression::GetName() const
{
	 return name;
}

