#include "IndexExpression.h"

FirstTask::CIndexExpression::CIndexExpression( std::shared_ptr<IExpression> theExpressionFirst,
	std::shared_ptr<IExpression> theExpressionSecond ) : 
	epressionFirst( theExpressionFirst ), expressionSecond( theExpressionSecond )
{
}

FirstTask::CIndexExpression::~CIndexExpression()
{
}