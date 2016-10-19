#include "ConstructorExpression.h"

FirstTask::CConstructorExpression::CConstructorExpression( std::shared_ptr<CIdExpression> theIdExpression ) :
	idExpression( theIdExpression )
{
}

FirstTask::CConstructorExpression::~CConstructorExpression()
{
}