#pragma once

#include "IRTreeAllClasses.h"

namespace Translate {

    class IRTSubtreeWrapper
    {
    public:
        virtual ~IRTSubtreeWrapper() {};
        virtual const std::shared_ptr<IRTree::IRTExpression> ToExpression() const = 0;
        virtual const std::shared_ptr<IRTree::IRTStatement> ToStatement() const = 0;
        virtual const std::shared_ptr<IRTree::IRTStatement> ToConditional( const std::shared_ptr<IRTree::Label> t, const std::shared_ptr<IRTree::Label> f ) const = 0;

    };
}