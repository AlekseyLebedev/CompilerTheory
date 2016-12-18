#include "IRTEBinop.h"

IRTree::IRTEBinop::IRTEBinop( RELOP _binop, const IRTExpression* _left, const IRTExpression* _right )
	: binop( _binop ), left( _left ), right( _right )
{
}

const IRTree::RELOP IRTree::IRTEBinop::GetBinop() const
{
    return binop;
}

const IRTree::IRTExpression* IRTree::IRTEBinop::GetLeft() const
{
	return left;
}

const IRTree::IRTExpression* IRTree::IRTEBinop::GetRight() const
{
	return right;
}

void IRTree::IRTEBinop::Accept( IVisitor* visitor ) const 
{
	visitor->Visit( this );
}
