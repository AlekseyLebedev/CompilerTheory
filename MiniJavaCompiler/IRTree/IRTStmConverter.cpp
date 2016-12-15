#include "IRTStmConverter.h"

Translate::IRTStmConverter::IRTStmConverter( const IRTree::IRTStatement* _stm ) : stm( _stm )
{}

const IRTree::IRTExpression* Translate::IRTStmConverter::ToExpression() const
{
    // Исправить
    return nullptr;
}

const IRTree::IRTStatement* Translate::IRTStmConverter::ToStatement() const
{
    return stm;
}

const IRTree::IRTStatement* Translate::IRTStmConverter::ToConditional( const IRTree::Label* t, const IRTree::Label* f ) const
{
    // Исправить
    return nullptr;
}
