#pragma once

#include "Translate.h"

namespace Translate {

    class IRTExpConverter : public IRTSubtreeWrapper
    {
    public:
        IRTExpConverter( const std::shared_ptr<IRTree::IRTExpression> _exp );
        const std::shared_ptr<IRTree::IRTExpression> ToExpression() const override;
        const std::shared_ptr<IRTree::IRTStatement> ToStatement() const override;
        const std::shared_ptr<IRTree::IRTStatement> ToConditional( const std::shared_ptr<IRTree::Label> t, const std::shared_ptr<IRTree::Label> f ) const override;

    private:
        const std::shared_ptr<IRTree::IRTExpression> exp;

    };
}