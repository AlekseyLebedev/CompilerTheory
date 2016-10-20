#include "ListConstructorExpression.h"

AbstractTreeGenerator::CListConstructorExpression::CListConstructorExpression( IExpression* theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CListConstructorExpression::~CListConstructorExpression()
{
}

void AbstractTreeGenerator::CListConstructorExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CListConstructorExpression::GetExpression() const
{
	 return expression;
}

