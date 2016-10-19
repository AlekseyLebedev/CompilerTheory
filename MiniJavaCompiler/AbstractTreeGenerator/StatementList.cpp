#include "StatementList.h"

AbstractTreeGenerator::CStatementList::CStatementList( std::shared_ptr<IStatement> theStatement,
	std::shared_ptr<CStatementList> theStatementList ) :
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
