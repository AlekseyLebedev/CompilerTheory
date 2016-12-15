#pragma once

#include "Translate.h"

namespace Translate {

    class IRTExpConverter : public IRTSubtreeWrapper
    {
    public:
        IRTExpConverter( const IRTree::IRTExpression* _exp );
        const IRTree::IRTExpression* ToExpression() const override;
        const IRTree::IRTStatement* ToStatement() const override;
        const IRTree::IRTStatement* ToConditional() const override;

    private:
        const IRTree::IRTExpression* exp;

    };
}