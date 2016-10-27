#include "ExpressionList.h"

AbstractTreeGenerator::CExpressionList::CExpressionList( IExpression* theExpression,
	CExpressionList* theExpressionList ) :
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
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CExpressionList::GetExpression() const
{
	 return expression;
}

const std::shared_ptr<AbstractTreeGenerator::CExpressionList> AbstractTreeGenerator::CExpressionList::GetExpressionList() const
{
	 return expressionList;
}

