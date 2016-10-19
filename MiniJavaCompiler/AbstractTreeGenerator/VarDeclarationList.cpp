#include "VarDeclarationList.h"

AbstractTreeGenerator::CVarDeclarationList::CVarDeclarationList( std::shared_ptr<CVarDeclaration> theVarDeclaration,
	std::shared_ptr<CVarDeclarationList> theVarDeclarationList ) :
	varDeclaration( theVarDeclaration ), varDeclarationList( theVarDeclarationList )
{
}

AbstractTreeGenerator::CVarDeclarationList::~CVarDeclarationList()
{
}

void AbstractTreeGenerator::CVarDeclarationList::Accept( IVisitor * v )
{
	v->visit( this );
}
