#include "VarDeclaration.h"

AbstractTreeGenerator::CVarDeclaration::CVarDeclaration( IType* theType,
	CIdExpression* theIdExpression ) :
	type( theType ), idExpression( theIdExpression )
{
}

AbstractTreeGenerator::CVarDeclaration::~CVarDeclaration()
{
}

void AbstractTreeGenerator::CVarDeclaration::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::IType> AbstractTreeGenerator::CVarDeclaration::GetType() const
{
	 return type;
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CVarDeclaration::GetIdExpression() const
{
	 return idExpression;
}

