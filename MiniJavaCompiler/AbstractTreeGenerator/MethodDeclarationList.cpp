#include "MethodDeclarationList.h"

AbstractTreeGenerator::CMethodDeclarationList::CMethodDeclarationList( CMethodDeclaration* theMethodDeclaration,
	CMethodDeclarationList* theMethodDeclarationList ) : 
	methodDeclaration( theMethodDeclaration ), methodDeclarationList( theMethodDeclarationList )
{
}

AbstractTreeGenerator::CMethodDeclarationList::~CMethodDeclarationList()
{
}

void AbstractTreeGenerator::CMethodDeclarationList::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::CMethodDeclaration> AbstractTreeGenerator::CMethodDeclarationList::GetMethodDeclaration() const
{
	 return methodDeclaration;
}

const std::shared_ptr<AbstractTreeGenerator::CMethodDeclarationList> AbstractTreeGenerator::CMethodDeclarationList::GetMethodDeclarationList() const
{
	 return methodDeclarationList;
}

