#include "IndexExpression.h"

AbstractTreeGenerator::CIndexExpression::CIndexExpression( std::shared_ptr<IExpression> theExpressionFirst,
	std::shared_ptr<IExpression> theExpressionSecond ) : 
	epressionFirst( theExpressionFirst ), expressionSecond( theExpressionSecond )
{
}

AbstractTreeGenerator::CIndexExpression::~CIndexExpression()
{
}

void AbstractTreeGenerator::CIndexExpression::Accept( IVisitor * v)
{
	v->visit( this );
}
