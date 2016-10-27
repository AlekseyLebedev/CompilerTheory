#include "AssignmentListStatement.h"

AbstractTreeGenerator::CAssignmentListStatement::CAssignmentListStatement( CIdExpression* theIdExpression,
	IExpression* theExpressionFirst,
	IExpression* theExpressionSecond ) :
	idExpression( theIdExpression ), expressionFirst( theExpressionFirst ), expressionSecond( theExpressionSecond )
{

}

AbstractTreeGenerator::CAssignmentListStatement::~CAssignmentListStatement()
{

}

void AbstractTreeGenerator::CAssignmentListStatement::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CAssignmentListStatement::GetIdExpression() const {
	 return idExpression;
}

const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CAssignmentListStatement::GetExpressionFirst() const {
	 return expressionFirst;
}

const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CAssignmentListStatement::GetExpressionSecond() const {
	 return expressionSecond;
}