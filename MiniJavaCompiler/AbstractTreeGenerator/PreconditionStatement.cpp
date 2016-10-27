#include "PreconditionStatement.h"

AbstractTreeGenerator::CPreconditionStatement::CPreconditionStatement( IExpression* theIdExpression,
	IStatement* theStatement ) :
	expression( theIdExpression ), statement( theStatement )
{
}

AbstractTreeGenerator::CPreconditionStatement::~CPreconditionStatement()
{
}

void AbstractTreeGenerator::CPreconditionStatement::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CPreconditionStatement::GetExpression() const
{
	 return expression;
}

const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CPreconditionStatement::GetStatement() const
{
	 return statement;
}

