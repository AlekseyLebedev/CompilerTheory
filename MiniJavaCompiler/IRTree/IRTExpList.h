#pragma once

#include "IRTreeClasses.h"

namespace IRTree {

    class IRTExpList
    {
    public:

        IRTExpList( const IRTExpression* _head, const IRTExpList* _tail );

        const IRTExpression* GetHead() const;
        const IRTExpList* GetTail() const;

        void Accept( IRTreeVisitor* visitor ) const;

    private:

        const IRTExpression* head;
        const IRTExpList* tail;

    };
}
