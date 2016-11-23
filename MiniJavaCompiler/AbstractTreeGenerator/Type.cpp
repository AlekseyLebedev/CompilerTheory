#include "Type.h"

AbstractTreeGenerator::CBasicType::CBasicType( AbstractTreeGenerator::TStandardType value ) : value( value )
{
}

int AbstractTreeGenerator::CBasicType::GetType() const
{
	return GetValue();
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

int AbstractTreeGenerator::CIdType::GetType() const
{
	return idExpression->GetName();
}

void AbstractTreeGenerator::CIdType::Accept( IVisitor * v )
{
	v->visit( this );
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CIdType::GetIdExpression() const
{
	return idExpression;
}
