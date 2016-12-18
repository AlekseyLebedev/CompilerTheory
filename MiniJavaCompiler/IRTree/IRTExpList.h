#pragma once

#include "IRTExpression.h"

namespace IRTree {

    class IRTExpList : public IRTExpression
    {
    public:

        IRTExpList( const IRTExpression* _head, const IRTExpList* _tail );

        const IRTExpression* GetHead() const;
        const IRTExpList* GetTail() const;

        void Accept( IVisitor* visitor ) const;

    private:

        const IRTExpression* head;
        const IRTExpList* tail;

    };
}
