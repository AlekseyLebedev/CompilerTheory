#include "ConstructorExpression.h"

AbstractTreeGenerator::CConstructorExpression::CConstructorExpression( std::shared_ptr<CIdExpression> theIdExpression ) :
	idExpression( theIdExpression )
{
}

AbstractTreeGenerator::CConstructorExpression::~CConstructorExpression()
{
}