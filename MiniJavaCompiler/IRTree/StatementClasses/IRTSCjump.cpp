#include <memory>
#include "IRTSCjump.h"

IRTree::IRTSCjump::IRTSCjump( const RELOP _relop, const std::shared_ptr<IRTExpression> _expLeft, const std::shared_ptr<IRTExpression> _expRight,
	const std::shared_ptr<Label> _labelLeft, const std::shared_ptr<Label> _labelRight )
    : relop( _relop ), expLeft( _expLeft ), expRight( _expRight ), labelLeft( _labelLeft ), labelRight( _labelRight )
{
}

const IRTree::RELOP IRTree::IRTSCjump::GetRelop() const
{
	return relop;
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTSCjump::GetExpLeft() const
{
	return expLeft;
}

const std::shared_ptr<IRTree::IRTExpression> IRTree::IRTSCjump::GetExpRight() const
{
	return expRight;
}

const std::shared_ptr<IRTree::Label> IRTree::IRTSCjump::GetLabelLeft() const
{
	return labelLeft;
}

const std::shared_ptr<IRTree::Label> IRTree::IRTSCjump::GetLabelRight() const
{
	return labelRight;
}

void IRTree::IRTSCjump::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
