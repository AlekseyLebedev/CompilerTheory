#include "ConstructorExpression.h"

AbstractTreeGenerator::CConstructorExpression::CConstructorExpression( std::shared_ptr<CIdExpression> theIdExpression ) :
	idExpression( theIdExpression )
{
}

AbstractTreeGenerator::CConstructorExpression::~CConstructorExpression()
{
}

void AbstractTreeGenerator::CConstructorExpression::Accept( IVisitor * v )
{
	v->visit( this );
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CConstructorExpression::GetIdExpression() const
{
	return idExpression;
}
