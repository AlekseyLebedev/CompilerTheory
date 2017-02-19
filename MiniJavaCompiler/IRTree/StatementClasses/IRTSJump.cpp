#include <memory>
#include "IRTSJump.h"

IRTree::IRTSJump::IRTSJump( const std::shared_ptr<Label> _label ) : label( _label )
{
}

const std::shared_ptr<IRTree::Label> IRTree::IRTSJump::GetLabel() const
{
	return label;
}

void IRTree::IRTSJump::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
