#include "IRTEName.h"

IRTree::IRTEName::IRTEName( const Label* _label ) : label( _label )
{
}

unsigned int IRTree::IRTEName::GetLabel() const
{
	return label;
}

void IRTree::IRTEName::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTEName::children() const
{
	return nullptr;
}
