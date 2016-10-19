#include "ParenExpression.h"

AbstractTreeGenerator::CParenExpression::CParenExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CParenExpression::~CParenExpression()
{
}