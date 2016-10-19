#include "ExpressionList.h"

FirstTask::CExpressionList::CExpressionList( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

FirstTask::CExpressionList::~CExpressionList()
{
}
