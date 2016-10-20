#include "ConstructorExpression.h"

AbstractTreeGenerator::CConstructorExpression::CConstructorExpression( CIdExpression* theIdExpression ) :
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
const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CConstructorExpression::GetIdExpression() const
{
	 return idExpression;
}

