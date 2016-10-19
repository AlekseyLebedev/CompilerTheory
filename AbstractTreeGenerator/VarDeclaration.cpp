#include "VarDeclaration.h"

FirstTask::CVarDeclaration::CVarDeclaration( std::shared_ptr<CType> theType,
	std::shared_ptr<CIdExpression> theIdExpression ) :
	type( theType ), idExpression( theIdExpression )
{
}

FirstTask::CVarDeclaration::~CVarDeclaration()
{
}