#include "IRTSMove.h"

IRTree::IRTSMove::IRTSMove( unsigned int _value ) : value( _value )
{
}

const IRTree::IRTExression* IRTree::IRTSMove::GetExrDst() const
{
	return dst;
}

const IRTree::IRTExression* IRTree::IRTSMove::GetExrSrc() const
{
	return src;
}

void IRTree::IRTSMove::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSMove::children() const
{
	//TO DO
	return nullptr;
}
