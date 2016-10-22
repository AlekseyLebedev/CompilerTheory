#include "AssignmentStatement.h"

AbstractTreeGenerator::CAssignmentStatement::CAssignmentStatement( CIdExpression* theIdExpression,
	IExpression* theExpression ) :
	idExpression( theIdExpression ), expression( theExpression )
{
}

AbstractTreeGenerator::CAssignmentStatement::~CAssignmentStatement()
{
}

void AbstractTreeGenerator::CAssignmentStatement::Accept( IVisitor * v )
{
	v->visit( this );
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CAssignmentStatement::GetIdExpression() const
{
	return idExpression;
}

const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CAssignmentStatement::GetExpression() const
{
	return expression;
}
