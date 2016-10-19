#include "MethodDeclarationList.h"

AbstractTreeGenerator::CMethodDeclarationList::CMethodDeclarationList( std::shared_ptr<CMethodDeclaration> theMethodDeclaration,
	std::shared_ptr<CMethodDeclarationList> theMethodDeclarationList ) : 
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
