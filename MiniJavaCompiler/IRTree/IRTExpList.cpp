#include "IRTExpList.h"

IRTree::IRTExpList::IRTExpList( const IRTExpression* _head, const IRTExpList* _tail ) : head( _head ), tail( _tail )
{
}

const IRTree::IRTExpression* IRTree::IRTExpList::GetHead() const
{
    return head;
}

const IRTree::IRTExpList* IRTree::IRTExpList::GetTail() const
{
    return tail;
}

void IRTree::IRTExpList::Accept( IRTreeVisitor* visitor ) const
{
    visitor->Visit( this );
}
