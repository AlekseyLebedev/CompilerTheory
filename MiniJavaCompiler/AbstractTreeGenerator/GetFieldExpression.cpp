#include "GetFieldExpression.h"

AbstractTreeGenerator::CGetFieldExpression::CGetFieldExpression( IExpression* theExpression,
	CIdExpression* theIdExpression,
	CExpressionList* theExpressionList ) :
	expression( theExpression ), idExpression( theIdExpression ), expressionList( theExpressionList )
{
}

AbstractTreeGenerator::CGetFieldExpression::~CGetFieldExpression()
{
}

void AbstractTreeGenerator::CGetFieldExpression::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CGetFieldExpression::GetExpression() const
{
	 return expression;
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CGetFieldExpression::GetIdExpression() const
{
	 return idExpression;
}

const std::shared_ptr<AbstractTreeGenerator::CExpressionList> AbstractTreeGenerator::CGetFieldExpression::GetExpressionList() const
{
	 return expressionList;
}

