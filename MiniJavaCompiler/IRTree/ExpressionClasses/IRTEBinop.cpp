#include "IRTEBinop.h"

IRTree::IRTEBinop::IRTEBinop( RELOP _binop, const std::shared_ptr<IRTExpression> _left, const std::shared_ptr<IRTExpression> _right )
	: binop( _binop ), left( _left ), right( _right )
{
}

const IRTree::RELOP IRTree::IRTEBinop::GetBinop() const
{
    return binop;
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTEBinop::GetLeft() const
{
	return left;
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTEBinop::GetRight() const
{
	return right;
}

void IRTree::IRTEBinop::Accept( IVisitor* visitor ) const 
{
	visitor->Visit( this );
}
