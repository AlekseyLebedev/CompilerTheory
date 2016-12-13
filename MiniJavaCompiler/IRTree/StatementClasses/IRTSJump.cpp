#include "IRTSJump.h"

IRTree::IRTSJump::IRTSJump( const IRTExression* _exp, const Label* _label )
	: exp( _exp ), label( _label )
{
}

const IRTree::IRTExpression* IRTree::IRTSJump::GetExp() const
{
	return exp;
}

const IRTree::Label* IRTree::IRTSJump::GetLabel() const
{
	return label;
}

void IRTree::IRTSJump::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSJump::children() const
{
	//TO DO
	return nullptr;
}
