#include "VarDeclaration.h"

AbstractTreeGenerator::CVarDeclaration::CVarDeclaration( CType* theType,
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
const std::shared_ptr<AbstractTreeGenerator::CType> AbstractTreeGenerator::CVarDeclaration::GetType() const
{
	 return type;
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CVarDeclaration::GetIdExpression() const
{
	 return idExpression;
}

