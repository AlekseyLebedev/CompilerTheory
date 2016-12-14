#include "IRTEName.h"

IRTree::IRTEName::IRTEName( const Label* _label ) : label( _label )
{
}

const IRTree::Label* IRTree::IRTEName::GetLabel() const
{
	return label;
}

void IRTree::IRTEName::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTEName::children() const
{
	return nullptr;
}
