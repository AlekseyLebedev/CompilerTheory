#include "Argument.h"

AbstractTreeGenerator::CArgument::CArgument( CType * theType, CIdExpression * theIdExpression ) :
	type( theType ), idExpression( theIdExpression )
{
}

AbstractTreeGenerator::CArgument::~CArgument()
{
}

const std::shared_ptr<AbstractTreeGenerator::CType> AbstractTreeGenerator::CArgument::GetType() const
{
	return type;
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CArgument::GetIdExpression() const
{
	return idExpression;
}

void AbstractTreeGenerator::CArgument::Accept( IVisitor * v )
{
	v->visit( this );
}
