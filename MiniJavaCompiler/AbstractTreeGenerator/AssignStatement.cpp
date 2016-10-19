#include "AssignmentStatement.h"

AbstractTreeGenerator::CAssignmentStatement::CAssignmentStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IExpression> theExpression ) :
	idExpression( theIdExpression), expression( theExpression )
{
}

AbstractTreeGenerator::CAssignmentStatement::~CAssignmentStatement()
{
}
