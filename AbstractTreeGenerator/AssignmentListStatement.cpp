#include "AssignmentListStatement.h"

FirstTask::CAssignmentListStatement::CAssignmentListStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IExpression> theExpressionFirst,
	std::shared_ptr<IExpression> theExpressionSecond ) :
	idExpression( theIdExpression ), expressionFirst( theExpressionFirst ), expressionSecond( theExpressionSecond )
{

}

FirstTask::CAssignmentListStatement::~CAssignmentListStatement()
{

}