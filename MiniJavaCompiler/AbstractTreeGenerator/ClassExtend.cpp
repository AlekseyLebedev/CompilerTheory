#include "ClassExtend.h"

AbstractTreeGenerator::CClassExtend::CClassExtend( std::shared_ptr<CIdExpression> theIdExpression ) :
	idExpression( theIdExpression )
{
}

AbstractTreeGenerator::CClassExtend::~CClassExtend()
{
}

void AbstractTreeGenerator::CClassExtend::Accept( IVisitor * V )
{
	v->visit( this );
}
