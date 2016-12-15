#include "IRTSJump.h"

IRTree::IRTSJump::IRTSJump( const Label* _label ) : label( _label )
{
}

const IRTree::Label* IRTree::IRTSJump::GetLabel() const
{
	return label;
}

void IRTree::IRTSJump::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSJump::children() const
{
	//TO DO
	return nullptr;
}
