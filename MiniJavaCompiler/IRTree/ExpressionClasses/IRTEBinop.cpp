#include "IRTEBinop.h"

IRTree::IRTEBinop::IRTEBinop( RELOP _binop, const IRTExpression* _left, const IRTExpression* _right )
	: binop( _binop ), left( _left ), right( _right )
{
}

const IRTree::IRTExpression* IRTree::IRTEBinop::GetLeft() const
{
	return left;
}

const IRTree::IRTExpression* IRTree::IRTEBinop::GetRight() const
{
	return right;
}

void IRTree::IRTEBinop::Accept( IRTreeVisitor* visitor ) const 
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTEBinop::children() const
{
    return new IRTExpList( left, new IRTExpList( right, nullptr ) );
}
