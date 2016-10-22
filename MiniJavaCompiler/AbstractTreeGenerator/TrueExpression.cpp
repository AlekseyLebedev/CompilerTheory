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

const bool AbstractTreeGenerator::CTrueExpression::GetBool() const
{
	 return value;
}

const bool AbstractTreeGenerator::CTrueExpression::GetValue() const
{
	return value;
}