#include "StatementList.h"

FirstTask::CStatementList::CStatementList( std::shared_ptr<IStatement> theStatement,
	std::shared_ptr<CStatementList> theStatementList = nullptr ) :
	statement ( theStatement ), statementList( theStatementList )
{
}

FirstTask::CStatementList::~CStatementList()
{
}