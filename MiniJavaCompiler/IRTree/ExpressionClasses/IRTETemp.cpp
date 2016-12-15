#include "IRTETemp.h"

IRTree::IRTETemp::IRTETemp( const Temp* _temp ) : temp( _temp )
{
}

const IRTree::Temp* IRTree::IRTETemp::GetTemp() const
{
    return temp;
}

void IRTree::IRTETemp::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTETemp::children() const
{
	return nullptr;
}
