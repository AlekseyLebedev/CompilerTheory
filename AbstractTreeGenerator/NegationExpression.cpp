#include "NegationExpression.h"

FirstTask::CNegationExpression::CNegationExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

FirstTask::CNegationExpression::~CNegationExpression()
{
}