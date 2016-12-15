#pragma once

#include "Translate.h"

namespace Translate
{

    class IRTStmConverter : public IRTSubtreeWrapper
    {
    public:
        IRTStmConverter( const IRTree::IRTStatement* _stm );
        const IRTree::IRTExpression* ToExpression() const override;
        const IRTree::IRTStatement* ToStatement() const override;
        const IRTree::IRTStatement* ToConditional( const IRTree::Label* t, const IRTree::Label* f ) const override;

    private:
        const IRTree::IRTStatement* stm;

    };
}