#include "PreconditionStatement.h"

AbstractTreeGenerator::CPreconditionStatement::CPreconditionStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IStatement> theStatement ) :
	idExpression( theIdExpression ), statement( theStatement )
{
}

AbstractTreeGenerator::CPreconditionStatement::~CPreconditionStatement()
{
}

void AbstractTreeGenerator::CPreconditionStatement::Accept( IVisitor * v )
{
	v->Visit( this );
}
