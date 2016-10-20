#include "CondtitionStatement.h"

AbstractTreeGenerator::CCondtitionStatement::CCondtitionStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IStatement> theStatementFirst, std::shared_ptr<IStatement> theStatementSecond ) :
	idExpression( theIdExpression ), statementFirst( theStatementFirst ), statementSecond( theStatementSecond )
{
}

AbstractTreeGenerator::CCondtitionStatement::~CCondtitionStatement()
{
}

void AbstractTreeGenerator::CCondtitionStatement::Accept( IVisitor * v )
{
	v->visit( this );
}
