#include "MethodDeclaration.h"

FirstTask::CMethodDeclaration::CMethodDeclaration( std::shared_ptr<CType> theType,
	std::shared_ptr<CIdExpression> theIdExpression,
	std::shared_ptr<CArgumentList> theArgumentList,
	std::shared_ptr<CVarDeclarationList>  theVarDeclarationList,
	std::shared_ptr<IExpression> theExpression ) : 
	type( theType ), idExpression( theIdExpression ), argumentList( theArgumentList ),
	varDeclarationList( theVarDeclarationList ), expression( theExpression )
{
}

FirstTask::CMethodDeclaration::~CMethodDeclaration()
{
}