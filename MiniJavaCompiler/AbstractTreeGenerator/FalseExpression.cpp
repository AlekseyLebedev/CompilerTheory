#include "FalseExpression.h"

AbstractTreeGenerator::CFalseExpression::CFalseExpression()
{
}

AbstractTreeGenerator::CFalseExpression::~CFalseExpression()
{
}

void AbstractTreeGenerator::CFalseExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
