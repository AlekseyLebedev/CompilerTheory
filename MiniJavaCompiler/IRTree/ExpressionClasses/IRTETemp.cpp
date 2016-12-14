#include "IRTETemp.h"

//TO DO
IRTree::IRTETemp::IRTETemp( )
{
}

void IRTree::IRTETemp::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTETemp::children() const
{
	return nullptr;
}
