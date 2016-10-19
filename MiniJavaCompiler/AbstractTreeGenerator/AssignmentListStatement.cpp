#include "AssignmentListStatement.h"

AbstractTreeGenerator::CAssignmentListStatement::CAssignmentListStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IExpression> theExpressionFirst,
	std::shared_ptr<IExpression> theExpressionSecond ) :
	idExpression( theIdExpression ), expressionFirst( theExpressionFirst ), expressionSecond( theExpressionSecond )
{

}

AbstractTreeGenerator::CAssignmentListStatement::~CAssignmentListStatement()
{

}

void AbstractTreeGenerator::CAssignmentListStatement::Accept( IVisitor * )
{
	v->visit( this );
}
