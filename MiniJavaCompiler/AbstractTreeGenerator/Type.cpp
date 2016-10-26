#include "Type.h"

AbstractTreeGenerator::CBasicType::CBasicType( const char * _name ) : name( _name )
{
}

void AbstractTreeGenerator::CBasicType::Accept( IVisitor * v )
{
	v->visit( this );
}

const char * AbstractTreeGenerator::CBasicType::GetName() const
{
	return name;
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
