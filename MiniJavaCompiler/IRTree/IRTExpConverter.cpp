#include <memory>
#include "IRTExpConverter.h"

Translate::IRTExpConverter::IRTExpConverter( const std::shared_ptr<IRTree::IRTExpression> _exp ) : exp( _exp )
{
}

const std::shared_ptr<IRTree::IRTExpression> Translate::IRTExpConverter::ToExpression() const
{
	return exp;
}

const std::shared_ptr<IRTree::IRTStatement> Translate::IRTExpConverter::ToStatement() const
{
	return std::make_shared<IRTree::IRTSExp>( exp );
}

const std::shared_ptr<IRTree::IRTStatement> Translate::IRTExpConverter::ToConditional( const std::shared_ptr<IRTree::Label> t, const std::shared_ptr<IRTree::Label> f ) const
{
	return std::make_shared<IRTree::IRTSCjump>( IRTree::CJUMP_NE, exp, std::make_shared<IRTree::IRTEConst>( 0 ), t, f );
}
