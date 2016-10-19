#include "NumExpression.h"

AbstractTreeGenerator::CNumExpression::CNumExpression( int theValue ) : value( theValue )
{
}

AbstractTreeGenerator::CNumExpression::~CNumExpression()
{
}

void AbstractTreeGenerator::CNumExpression::Accept( IVisitor* v )
{
	v->Visit( this );
}