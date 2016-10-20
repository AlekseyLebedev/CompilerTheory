#include "StatementList.h"

AbstractTreeGenerator::CStatementList::CStatementList( IStatement* theStatement,
	CStatementList* theStatementList ) :
	statement ( theStatement ), statementList( theStatementList )
{
}

AbstractTreeGenerator::CStatementList::~CStatementList()
{
}

void AbstractTreeGenerator::CStatementList::Accept( IVisitor * v)
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CStatementList::GetStatement() const
{
	 return statement;
}

const std::shared_ptr<AbstractTreeGenerator::CStatementList> AbstractTreeGenerator::CStatementList::GetStatementList() const
{
	 return statementList;
}

