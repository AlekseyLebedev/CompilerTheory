#include <memory>
#include "IRTEMem.h"

IRTree::IRTEMem::IRTEMem( std::shared_ptr<IRTExpression> _exp ) : exp( _exp )
{
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTEMem::GetExp() const
{
	return exp;
}

void IRTree::IRTEMem::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
