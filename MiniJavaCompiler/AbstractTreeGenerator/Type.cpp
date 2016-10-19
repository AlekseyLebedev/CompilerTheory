#include "Type.h"

AbstractTreeGenerator::CType::CType( std::shared_ptr<CIdExpression> theIdExpression ) :
	idExpression ( theIdExpression ) 
{
}

AbstractTreeGenerator::CType::~CType()
{
}

void AbstractTreeGenerator::CType::Accept( IVisitor * v )
{
	v->Visit( this );
}
