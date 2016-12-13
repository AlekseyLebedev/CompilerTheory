#include "IRTETemp.h"

//TO DO
IRTree::IRTETemp::IRTETemp( )
{
}

void IRTree::IRTETemp::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTETemp::children() const
{
	return nullptr;
}
