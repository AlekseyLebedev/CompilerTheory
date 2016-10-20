#include "VarDeclarationList.h"

AbstractTreeGenerator::CVarDeclarationList::CVarDeclarationList( CVarDeclaration* theVarDeclaration,
	CVarDeclarationList* theVarDeclarationList ) :
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
const std::shared_ptr<AbstractTreeGenerator::CVarDeclaration> AbstractTreeGenerator::CVarDeclarationList::GetVarDeclaration() const
{
	 return varDeclaration;
}

const std::shared_ptr<AbstractTreeGenerator::CVarDeclarationList> AbstractTreeGenerator::CVarDeclarationList::GetVarDeclarationList() const
{
	 return varDeclarationList;
}

