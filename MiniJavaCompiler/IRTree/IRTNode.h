#pragma once

#include "IRTreeClasses.h"

namespace IRTree
{

    class IRTNode
    {
    public:

        virtual ~IRTNode() {};
        virtual void Accept( IRTreeVisitor* visitor ) const = 0;
        virtual const IRTExpList* children() const = 0;

    };
}
