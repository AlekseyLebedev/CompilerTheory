#include <memory>
#include "IRTSLabel.h"

IRTree::IRTSLabel::IRTSLabel( const std::shared_ptr<Label> _label ) : label( _label )
{
}

const std::shared_ptr<IRTree::Label> IRTree::IRTSLabel::GetLabel() const
{
	return label;
}

void IRTree::IRTSLabel::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
