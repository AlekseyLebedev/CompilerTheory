#include <memory>
#include "IRTEEseq.h"

IRTree::IRTEEseq::IRTEEseq( const std::shared_ptr<IRTStatement> _stm, const std::shared_ptr<IRTExpression> _exp )
	: stm( _stm ), exp( _exp )
{
}

const std::shared_ptr<IRTree::IRTStatement> IRTree::IRTEEseq::GetStm() const
{
	return stm;
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTEEseq::GetExp() const
{
	return exp;
}

void IRTree::IRTEEseq::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
