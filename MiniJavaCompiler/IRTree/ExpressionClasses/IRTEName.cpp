#include <memory>
#include "IRTEName.h"

IRTree::IRTEName::IRTEName( const std::shared_ptr<Label> _label ) : label( _label )
{
}

const std::shared_ptr<IRTree::Label> IRTree::IRTEName::GetLabel() const
{
	return label;
}

void IRTree::IRTEName::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
