#include "VarDeclarationList.h"

FirstTask::CVarDeclarationList::CVarDeclarationList( std::shared_ptr<CVarDeclaration> theVarDeclaration,
	std::shared_ptr<CVarDeclarationList> theVarDeclarationList ) :
	varDeclaration( theVarDeclaration ), varDeclarationList( theVarDeclarationList )
{
}

FirstTask::CVarDeclarationList::~CVarDeclarationList()
{
}