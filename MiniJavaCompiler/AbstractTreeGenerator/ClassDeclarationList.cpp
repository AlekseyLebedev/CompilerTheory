#include "ClassDeclarationList.h"

AbstractTreeGenerator::CClassDeclarationList::CClassDeclarationList( CClassDeclaration* theClassDeclaration,
	CClassDeclarationList* theClassDeclarationList ) :
	classDeclaration( theClassDeclaration ), classDeclarationList( theClassDeclarationList )
{

}

AbstractTreeGenerator::CClassDeclarationList::~CClassDeclarationList()
{

}

void AbstractTreeGenerator::CClassDeclarationList::Accept( IVisitor * v )
{
	v->visit( this );

}
const std::shared_ptr<AbstractTreeGenerator::CClassDeclaration> AbstractTreeGenerator::CClassDeclarationList::GetClassDeclaration() const
{
	 return classDeclaration;
}

const std::shared_ptr<AbstractTreeGenerator::CClassDeclarationList> AbstractTreeGenerator::CClassDeclarationList::GetClassDeclarationList() const
{
	 return classDeclarationList;
}

