#include "IRTSLabel.h"

IRTree::IRTSLabel::IRTSLabel( const Label* _label ) : label( _label )
{
}

const IRTree::Label* IRTree::IRTSLabel::GetLabel() const
{
	return label;
}

void IRTree::IRTSLabel::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
