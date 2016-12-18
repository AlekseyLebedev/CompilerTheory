#include "IRTEMem.h"

IRTree::IRTEMem::IRTEMem( IRTExpression* _exp ) : exp( _exp )
{
}

const IRTree::IRTExpression* IRTree::IRTEMem::GetExp() const
{
	return exp;
}

void IRTree::IRTEMem::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
