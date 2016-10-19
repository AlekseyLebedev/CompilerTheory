#include "LengthExpression.h"

AbstractTreeGenerator::CLengthExpression::CLengthExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CLengthExpression::~CLengthExpression()
{
}
