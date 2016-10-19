#include "ThisExpression.h"

AbstractTreeGenerator::CThisExpression::CThisExpression()
{
}

AbstractTreeGenerator::CThisExpression::~CThisExpression()
{
}

void AbstractTreeGenerator::CThisExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
