#include "ListConstructorExpression.h"

AbstractTreeGenerator::CListConstructorExpression::CListConstructorExpression( std::shared_ptr<IExpression> theExpression ) :
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
