#include "ConditionStatement.h"

AbstractTreeGenerator::CConditionStatement::CConditionStatement( CIdExpression* theIdExpression,
	IStatement* theStatementFirst, IStatement* theStatementSecond ) :
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
const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CConditionStatement::GetIdExpression() const
{
	 return idExpression;
}

const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CConditionStatement::GetStatementFirst() const
{
	 return statementFirst;
}

const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CConditionStatement::GetStatementSecond() const
{
	 return statementSecond;
}

