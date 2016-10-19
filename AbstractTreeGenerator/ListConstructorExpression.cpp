#include "ListConstructorExpression.h"

FirstTask::CListConstructorExpression::CListConstructorExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

FirstTask::CListConstructorExpression::~CListConstructorExpression()
{
}