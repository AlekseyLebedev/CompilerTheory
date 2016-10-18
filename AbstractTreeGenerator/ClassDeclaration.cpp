#include "ClassDeclaration.h"

FirstTask::CClassDeclaration::CClassDeclaration( std::shared_ptr<CClassDeclaration> theClassDeclaration,
	std::shared_ptr<CClassDeclarationList> theClassDeclarationList = nullptr ) :
	classDeclaration( theClassDeclaration ), classDeclarationList( theClassDeclarationList )
{
}

FirstTask::CClassDeclaration::~CClassDeclaration()
{
}