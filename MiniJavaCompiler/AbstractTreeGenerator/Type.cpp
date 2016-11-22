#include "Type.h"

AbstractTreeGenerator::CBasicType::CBasicType( AbstractTreeGenerator::TStandardType value ) : value( value )
{
}

void AbstractTreeGenerator::CBasicType::Accept( IVisitor * v )
{
	v->visit( this );
}

AbstractTreeGenerator::TStandardType AbstractTreeGenerator::CBasicType::GetValue() const
{
	return value;
}

AbstractTreeGenerator::CIdType::CIdType( CIdExpression * theIdExpression ) : idExpression( theIdExpression )
{
}

void AbstractTreeGenerator::CIdType::Accept( IVisitor * v )
{
	v->visit( this );
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CIdType::GetIdExpression() const
{
	return idExpression;
}
