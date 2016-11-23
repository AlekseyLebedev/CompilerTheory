#include "Type.h"

AbstractTreeGenerator::CBasicType::CBasicType( AbstractTreeGenerator::TStandardType value ) : value( value )
{
}

std::string AbstractTreeGenerator::CBasicType::GetType() const
{
	return std::string("Basic");
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

std::string AbstractTreeGenerator::CIdType::GetType() const
{
	return std::string("POD");
}

void AbstractTreeGenerator::CIdType::Accept( IVisitor * v )
{
	v->visit( this );
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CIdType::GetIdExpression() const
{
	return idExpression;
}
