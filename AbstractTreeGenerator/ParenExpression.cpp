#include "ParenExpression.h"

FirstTask::CParenExpression::CParenExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

FirstTask::CParenExpression::~CParenExpression()
{
}