#include "TrueExpression.h"

AbstractTreeGenerator::CTrueExpression::CTrueExpression()
{
}

AbstractTreeGenerator::CTrueExpression::~CTrueExpression()
{
}

void AbstractTreeGenerator::CTrueExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
const const AbstractTreeGenerator::CTrueExpression::GetBool() const
{
	 return bool;
}

