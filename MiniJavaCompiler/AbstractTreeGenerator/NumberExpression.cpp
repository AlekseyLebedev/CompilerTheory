#include "NumberExpression.h"
//123

AbstractTreeGenerator::CNumberExpression::CNumberExpression( int theValue ) : value( theValue )
{
}

AbstractTreeGenerator::CNumberExpression::~CNumberExpression()
{
}

void AbstractTreeGenerator::CNumberExpression::Accept( IVisitor* v )
{
	v->visit( this );
}