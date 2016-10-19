#include "VarDeclaration.h"

AbstractTreeGenerator::CVarDeclaration::CVarDeclaration( std::shared_ptr<CType> theType,
	std::shared_ptr<CIdExpression> theIdExpression ) :
	type( theType ), idExpression( theIdExpression )
{
}

AbstractTreeGenerator::CVarDeclaration::~CVarDeclaration()
{
}