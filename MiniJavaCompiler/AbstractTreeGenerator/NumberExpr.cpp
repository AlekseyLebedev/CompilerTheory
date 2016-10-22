#include "NumberExpr.h"


AbstractTreeGenerator::CNumberExpr::CNumberExpr( int val ) :
	value( val )
{
}

AbstractTreeGenerator::CNumberExpr::~CNumberExpr()
{
}


void AbstractTreeGenerator::CNumberExpr::Accept( IVisitor * v )
{
	v->visit( this );
}
const int AbstractTreeGenerator::CNumberExpr::GetValue() const
{
	 return value;
}

