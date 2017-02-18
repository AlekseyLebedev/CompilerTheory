#include <memory>
#include "IRTStmConverter.h"

Translate::IRTStmConverter::IRTStmConverter( const std::shared_ptr<IRTree::IRTStatement> _stm ) : stm( _stm )
{}

const std::shared_ptr<IRTree::IRTExpression> Translate::IRTStmConverter::ToExpression() const
{
    // Исправить
    return nullptr;
}

const std::shared_ptr<IRTree::IRTStatement> Translate::IRTStmConverter::ToStatement() const
{
    return stm;
}

const std::shared_ptr<IRTree::IRTStatement> Translate::IRTStmConverter::ToConditional( const std::shared_ptr<IRTree::Label> t, const std::shared_ptr<IRTree::Label> f ) const
{
    // Исправить
    return nullptr;
}
