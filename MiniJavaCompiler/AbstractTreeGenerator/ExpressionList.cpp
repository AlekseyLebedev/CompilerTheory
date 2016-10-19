#include "ExpressionList.h"

AbstractTreeGenerator::CExpressionList::CExpressionList( std::shared_ptr<IExpression> theExpression ) :
	expression( theExpression )
{
}

AbstractTreeGenerator::CExpressionList::~CExpressionList()
{
}

void AbstractTreeGenerator::CExpressionList::Accept( IVisitor * v )
{
	v->visit( this );
}
