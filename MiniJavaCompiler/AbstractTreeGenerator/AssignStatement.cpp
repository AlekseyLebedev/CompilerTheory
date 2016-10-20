#include "AssignmentStatement.h"

AbstractTreeGenerator::CAssignmentStatement::CAssignmentStatement( CAssignmentStatement::CIdExpression* theIdExpression, CAssignmentStatement::IExpression* theExpression ) :
	idExpression( theIdExpression ), expression( theExpression )
{
}

AbstractTreeGenerator::CAssignmentStatement::~CAssignmentStatement()
{
}
const std::string AbstractTreeGenerator::CAssignStatement::GetVariableName() const
{
	return variableName;
}

const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CAssignStatement::GetExpression() const
{
	return expression;
}
