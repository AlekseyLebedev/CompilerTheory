#include <memory>
#include "IRTSExp.h"

IRTree::IRTSExp::IRTSExp( const std::shared_ptr<IRTExpression> _exp ) : exp( _exp )
{
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTSExp::GetExp() const
{
	return exp;
}

void IRTree::IRTSExp::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
