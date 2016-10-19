#include "ClassDeclarationList.h"

FirstTask::CClassDeclarationList::CClassDeclarationList( std::shared_ptr<CClassDeclaration> theClassDeclaration,
	std::shared_ptr<CClassDeclarationList> theClassDeclarationList ) :
	classDeclaration( theClassDeclaration ), classDeclarationList( theClassDeclarationList )
{

}

FirstTask::CClassDeclarationList::~CClassDeclarationList()
{

}