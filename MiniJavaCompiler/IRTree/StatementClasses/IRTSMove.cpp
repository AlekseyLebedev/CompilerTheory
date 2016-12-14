#include "IRTSMove.h"

IRTree::IRTSMove::IRTSMove( const IRTExpression* _dst, const IRTExpression* _src )
	: dst( _dst ), src( _src )
{
}

const IRTree::IRTExpression* IRTree::IRTSMove::GetExrDst() const
{
	return dst;
}

const IRTree::IRTExpression* IRTree::IRTSMove::GetExrSrc() const
{
	return src;
}

void IRTree::IRTSMove::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSMove::children() const
{
	//TO DO
	return nullptr;
}
