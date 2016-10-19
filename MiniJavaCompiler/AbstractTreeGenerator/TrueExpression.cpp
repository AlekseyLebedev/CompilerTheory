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
