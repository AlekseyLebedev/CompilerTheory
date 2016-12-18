#include "IRTECall.h"

IRTree::IRTECall::IRTECall( const IRTExpression* _func, const IRTExpList* _args )
	: func( _func ), args( _args )
{
}

const IRTree::IRTExpression* IRTree::IRTECall::GetFunc() const
{
	return func;
}

const IRTree::IRTExpList* IRTree::IRTECall::GetArgs() const
{
	return args;
}

void IRTree::IRTECall::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
