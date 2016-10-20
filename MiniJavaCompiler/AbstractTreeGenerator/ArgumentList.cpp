#include "ArgumentList.h"

AbstractTreeGenerator::CArgumentList::CArgumentList( CArgument * theArgument, CArgumentList * theArgumentList ) :
	argument( theArgument ), argumentList( theArgumentList )
{
}

AbstractTreeGenerator::CArgumentList::~CArgumentList()
{
}

const std::shared_ptr<AbstractTreeGenerator::CArgument> AbstractTreeGenerator::CArgumentList::GetArgument() const
{
	return argument;
}

const std::shared_ptr<AbstractTreeGenerator::CArgumentList> AbstractTreeGenerator::CArgumentList::GetArgumentList() const
{
	return argumentList;
}

void AbstractTreeGenerator::CArgumentList::Accept( IVisitor * v )
{
	v->visit( this );
}
