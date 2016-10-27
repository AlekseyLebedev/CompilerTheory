#include "ParenExpression.h"

AbstractTreeGenerator::CParenExpression::CParenExpression( IExpression* theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CParenExpression::~CParenExpression()
{
}

void AbstractTreeGenerator::CParenExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CParenExpression::GetExpression() const
{
	 return expression;
}

