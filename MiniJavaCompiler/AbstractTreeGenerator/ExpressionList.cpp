#include "ExpressionList.h"

AbstractTreeGenerator::CExpressionList::CExpressionList( std::shared_ptr<IExpression> theExpression,
	std::shared_ptr<CExpressionList> theExpressionList ) :
	expression( theExpression ), expressionList( theExpressionList )
{
}

AbstractTreeGenerator::CExpressionList::~CExpressionList()
{
}

void AbstractTreeGenerator::CExpressionList::Accept( IVisitor * v )
{
	v->visit( this );
}
