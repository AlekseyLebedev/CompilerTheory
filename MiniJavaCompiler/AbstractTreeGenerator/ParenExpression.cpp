#include "ParenExpression.h"

AbstractTreeGenerator::CParenExpression::CParenExpression( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CParenExpression::~CParenExpression()
{
}

void AbstractTreeGenerator::CParenExpression::Accept( IVisitor * v )
{
	v->Visit( this );
}
