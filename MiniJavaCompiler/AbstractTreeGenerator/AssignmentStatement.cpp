#include "AssignmentStatement.h"

AbstractTreeGenerator::CAssignmentStatement::CAssignmentStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IExpression> theExpression ) :
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
