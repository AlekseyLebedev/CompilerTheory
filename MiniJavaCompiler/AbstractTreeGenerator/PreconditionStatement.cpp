#include "PreconditionStatement.h"

AbstractTreeGenerator::CPreconditionStatement::CPreconditionStatement( CIdExpression* theIdExpression,
	IStatement* theStatement ) :
	idExpression( theIdExpression ), statement( theStatement )
{
}

AbstractTreeGenerator::CPreconditionStatement::~CPreconditionStatement()
{
}

void AbstractTreeGenerator::CPreconditionStatement::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CPreconditionStatement::GetIdExpression() const
{
	 return idExpression;
}

const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CPreconditionStatement::GetStatement() const
{
	 return statement;
}

