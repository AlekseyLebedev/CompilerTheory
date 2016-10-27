#include "ConditionStatement.h"

AbstractTreeGenerator::CConditionStatement::CConditionStatement( IExpression* theIdExpression,
	IStatement* theStatementFirst, IStatement* theStatementSecond ) :
	expression( theIdExpression ), statementFirst( theStatementFirst ), statementSecond( theStatementSecond )
{
}

AbstractTreeGenerator::CConditionStatement::~CConditionStatement()
{
}

void AbstractTreeGenerator::CConditionStatement::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CConditionStatement::GetExpression() const
{
	 return expression;
}

const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CConditionStatement::GetStatementFirst() const
{
	 return statementFirst;
}

const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CConditionStatement::GetStatementSecond() const
{
	 return statementSecond;
}

