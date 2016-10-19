#include "PreconditionStatement.h"

FirstTask::CPreconditionStatement::CPreconditionStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IStatement> theStatement ) :
	idExpression( theIdExpression ), statement( theStatement )
{
}

FirstTask::CPreconditionStatement::~CPreconditionStatement()
{
}
