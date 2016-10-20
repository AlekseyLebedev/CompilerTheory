#include "Type.h"

AbstractTreeGenerator::CType::CType( const char* id ) :
	idExpression ( id ) 
{
}

AbstractTreeGenerator::CType::~CType()
{
}

void AbstractTreeGenerator::CType::Accept( IVisitor * v )
{
	v->visit( this );
}
