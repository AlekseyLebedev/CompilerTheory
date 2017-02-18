#include <memory>
#include "IRTSMove.h"

IRTree::IRTSMove::IRTSMove( const std::shared_ptr<IRTExpression> _dst, const std::shared_ptr<IRTExpression> _src )
	: dst( _dst ), src( _src )
{
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTSMove::GetExrDst() const
{
	return dst;
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTSMove::GetExrSrc() const
{
	return src;
}

void IRTree::IRTSMove::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
