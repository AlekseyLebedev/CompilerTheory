#include "ArgumentList.h"

AbstractTreeGenerator::CArgumentList::CArgumentList( std::shared_ptr<CArgument> theArgument,
	std::shared_ptr<CArgumentList> theArgumentList ) :
	argument( theArgument ), argumentList( theArgumentList )
{
}

AbstractTreeGenerator::CArgumentList::~CArgumentList()
{
}

void AbstractTreeGenerator::CArgumentList::Accept( IVisitor * v )
{
	v->visit( this );
}
