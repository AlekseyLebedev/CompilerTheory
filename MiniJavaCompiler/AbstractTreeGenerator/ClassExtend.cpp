#include "ClassExtend.h"

AbstractTreeGenerator::CClassExtend::CClassExtend( CIdExpression* theIdExpression ) :
	idExpression( theIdExpression )
{
}

AbstractTreeGenerator::CClassExtend::~CClassExtend()
{
}

void AbstractTreeGenerator::CClassExtend::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CClassExtend::GetIdExpression() const
{
	 return idExpression;
}

