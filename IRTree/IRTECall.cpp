#include "IRTECall.h"

IRTree::IRTECall::IRTECall( const IRTExpression* _func, const IRTExpList* _args )
	func( _func ), args( _args )
{
}

const IRTree::IRTExpression* IRTree::IRTECall::GetExp() const
{
	return func;
}

const IRTree::IRTExpList* IRTree::IRTECall::GetExpList() const
{
	return args;
}

void IRTree::IRTECall::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTECall::children() const
{
	return new IRTExpList( func, args );
}
