#pragma once

#include "IRTreeClasses.h"

namespace Translate {

    class IRTSubtreeWrapper
    {
    public:
        virtual ~IRTSubtreeWrapper() {};
        virtual const IRTree::IRTExpression* ToExpression() const = 0;
        virtual const IRTree::IRTStatement* ToStatement() const = 0;
        virtual const IRTree::IRTStatement* ToConditional( const IRTree::Label* t, const IRTree::Label* f ) const = 0;

    };
}