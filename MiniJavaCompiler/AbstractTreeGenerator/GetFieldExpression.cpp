#include "GetFieldExpression.h"

AbstractTreeGenerator::CGetFieldExpression::CGetFieldExpression( std::shared_ptr<IExpression> theExpression,
	std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<CExpressionList> theExpressionList ) :
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
