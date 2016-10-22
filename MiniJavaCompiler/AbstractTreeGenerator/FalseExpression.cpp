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

const bool AbstractTreeGenerator::CFalseExpression::GetBool() const
{
	 return value;
}

const bool AbstractTreeGenerator::CFalseExpression::GetValue() const
{
	return value;
}

