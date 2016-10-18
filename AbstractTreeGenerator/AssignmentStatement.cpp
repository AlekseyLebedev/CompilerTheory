#include "AssignmentStatement.h"

FirstTask::CAssignmentStatement::CAssignmentStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IExpression> theExpression ) :
	idExpression( theIdExpression ), expression( theExpression )
{
}

FirstTask::CAssignmentStatement::~CAssignmentStatement()
{
}
