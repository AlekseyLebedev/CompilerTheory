#include "MethodDeclarationList.h"

FirstTask::CMethodDeclarationList::CMethodDeclarationList( std::shared_ptr<CMethodDeclaration> theMethodDeclaration,
	std::shared_ptr<CMethodDeclarationList> theMethodDeclarationList ) : 
	methodDeclaration( theMethodDeclaration ), methodDeclarationList( theMethodDeclarationList )
{
}

FirstTask::CMethodDeclarationList::~CMethodDeclarationList()
{
}