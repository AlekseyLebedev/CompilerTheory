#include "LengthExpression.h"

AbstractTreeGenerator::CLengthExpression::CLengthExpression( IExpression* theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CLengthExpression::~CLengthExpression()
{
}

void AbstractTreeGenerator::CLengthExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CLengthExpression::GetExpression() const
{
	 return expression;
}

