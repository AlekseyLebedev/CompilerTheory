#include "ClassDeclarationList.h"

AbstractTreeGenerator::CClassDeclarationList::CClassDeclarationList( std::shared_ptr<CClassDeclaration> theClassDeclaration,
	std::shared_ptr<CClassDeclarationList> theClassDeclarationList ) :
	classDeclaration( theClassDeclaration ), classDeclarationList( theClassDeclarationList )
{

}

AbstractTreeGenerator::CClassDeclarationList::~CClassDeclarationList()
{

}