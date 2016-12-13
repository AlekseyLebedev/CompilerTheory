#include "IRTEMem.h"

IRTree::IRTEMem::IRTEMem( IRTExpression* _expr ) : exp( _expr )
{
}

const IRTree::IRTExpression* IRTree::IRTEMem::GetExp() const
{
	return exp;
}

void IRTree::IRTEMem::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTEMem::children() const
{
	return new CExpList( exp, nullptr );
}
