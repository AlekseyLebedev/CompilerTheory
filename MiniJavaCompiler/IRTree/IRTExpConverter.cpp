#include "IRTExpConverter.h"

Translate::IRTExpConverter::IRTExpConverter( const IRTree::IRTExpression* _exp ) : exp( _exp )
{
}

const IRTree::IRTExpression* Translate::IRTExpConverter::ToExpression() const
{
    return exp;
}

const IRTree::IRTStatement* Translate::IRTExpConverter::ToStatement() const
{
    return new IRTree::IRTSExp( exp );
}

const IRTree::IRTStatement* Translate::IRTExpConverter::ToConditional( const IRTree::Label* t, const IRTree::Label* f ) const
{
    return new IRTree::IRTSCjump( IRTree::CJUMP_NE, exp, new IRTree::IRTEConst(0), t, f );
}
