#include <memory>
#include "IRTECall.h"

IRTree::IRTECall::IRTECall( const std::shared_ptr<IRTExpression> _func, const std::shared_ptr<IRTExpList> _args )
	: func( _func ), args( _args )
{
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTECall::GetFunc() const
{
	return func;
}

const std::shared_ptr<IRTree::IRTExpList> IRTree::IRTECall::GetArgs() const
{
	return args;
}

void IRTree::IRTECall::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
