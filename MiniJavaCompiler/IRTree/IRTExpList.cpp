#include <memory>
#include "IRTExpList.h"

IRTree::IRTExpList::IRTExpList( const std::shared_ptr<IRTExpression> _head, const std::shared_ptr<IRTExpList> _tail ) : head( _head ), tail( _tail )
{
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTExpList::GetHead() const
{
    return head;
}

const std::shared_ptr<IRTree::IRTExpList> IRTree::IRTExpList::GetTail() const
{
    return tail;
}

std::shared_ptr<IRTree::IRTExpression> IRTree::IRTExpList::GetHead()
{
	return head;
}

std::shared_ptr<IRTree::IRTExpList> IRTree::IRTExpList::GetTail()
{
	return tail;
}

void IRTree::IRTExpList::Accept( IVisitor* visitor ) const
{
    visitor->Visit( this );
}
