#include "IRTSSeq.h"

IRTree::IRTSSeq::IRTSSeq( const IRTStatement* _left, const IRTStatement* _right ) : left( _left ), right( _right )
{
}

const IRTree::IRTStatement* IRTree::IRTSSeq::GetStmLeft() const
{
	return left;
}

const IRTree::IRTStatement* IRTree::IRTSSeq::GetStmRight() const
{
	return right;
}

void IRTree::IRTSSeq::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}
