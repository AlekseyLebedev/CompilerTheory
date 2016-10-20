#include "IndexExpression.h"

AbstractTreeGenerator::CIndexExpression::CIndexExpression( IExpression* theExpressionFirst,
	IExpression* theExpressionSecond ) : 
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
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CIndexExpression::GetEpressionFirst() const
{
	 return epressionFirst;
}

const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CIndexExpression::GetExpressionSecond() const
{
	 return expressionSecond;
}

