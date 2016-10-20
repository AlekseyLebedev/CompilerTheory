#include "NegationExpression.h"

AbstractTreeGenerator::CNegationExpression::CNegationExpression( IExpression* theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CNegationExpression::~CNegationExpression()
{
}

void AbstractTreeGenerator::CNegationExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CNegationExpression::GetExpression() const
{
	 return expression;
}

