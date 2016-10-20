#include "ConditionStatement.h"

AbstractTreeGenerator::CConditionStatement::CConditionStatement( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<IStatement> theStatementFirst, std::shared_ptr<IStatement> theStatementSecond ) :
	idExpression( theIdExpression ), statementFirst( theStatementFirst ), statementSecond( theStatementSecond )
{
}

AbstractTreeGenerator::CConditionStatement::~CConditionStatement()
{
}

void AbstractTreeGenerator::CConditionStatement::Accept( IVisitor * v )
{
	v->visit( this );
}
