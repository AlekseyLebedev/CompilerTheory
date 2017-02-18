#include <memory>
#include "IRTSSeq.h"

IRTree::IRTSSeq::IRTSSeq( const std::shared_ptr<IRTStatement> _left, const std::shared_ptr<IRTStatement> _right ) : left( _left ), right( _right )
{
}

const std::shared_ptr<IRTree::IRTStatement> IRTree::IRTSSeq::GetStmLeft() const
{
	return left;
}

const std::shared_ptr<IRTree::IRTStatement> IRTree::IRTSSeq::GetStmRight() const
{
	return right;
}

void IRTree::IRTSSeq::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
