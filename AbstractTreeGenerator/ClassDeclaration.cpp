#include "ClassDeclaration.h"

FirstTask::CClassDeclaration::CClassDeclaration( std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<CClassExtend> theClassExtend,
	std::shared_ptr<CVarDeclarationList> theVarDeclarationList,
	std::shared_ptr<CMethodDeclarationList> theMethodDeclarationList ) :
	idExpression( theIdExpression ), classExtend( theClassExtend ),
	varDeclarationList( theVarDeclarationList ), methodDeclarationList( theMethodDeclarationList )
{
}

FirstTask::CClassDeclaration::~CClassDeclaration()
{
}