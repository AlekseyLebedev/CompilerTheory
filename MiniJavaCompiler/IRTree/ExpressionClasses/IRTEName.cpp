#include "IRTEName.h"

IRTree::IRTEName::IRTEName( const Label* _label ) : label( _label )
{
}

const IRTree::Label* IRTree::IRTEName::GetLabel() const
{
	return label;
}

void IRTree::IRTEName::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
