#include "CondtitionStatement.h"

AbstractTreeGenerator::CondtitionStatement::CondtitionStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IStatement> theStatementFirst, std::shared_ptr<IStatement> theStatementSecond ) :
	idExpression( theIdExpression ), statementFirst( theStatementFirst ), statementSecond( theStatementSecond )
{
}

AbstractTreeGenerator::CondtitionStatement::~CondtitionStatement()
{
}
