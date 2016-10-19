#include "NumberExpr.h"


AbstractTreeGenerator::CNumberExpr::CNumberExpr( int val ) :
	value( val )
{
}


void AbstractTreeGenerator::CNumberExpr::Accept( IVisitor * v )
{
	v->visit( this );
}
