#include "IRTSCjump.h"

IRTree::IRTSCjump::IRTSCjump( const RELOP _relop, const IRTExpression* _expLeft, const IRTExpression* _expRight,
	const Label* _labelLeft, const Label* _labelRight )
    : relop( _relop ), expLeft( _expLeft ), expRight( _expRight ), labelLeft( _labelLeft ), labelRight( _labelRight )
{
}

const IRTree::RELOP IRTree::IRTSCjump::GetRelop() const
{
	return relop;
}

const IRTree::IRTExpression* IRTree::IRTSCjump::GetExpLeft() const
{
	return expLeft;
}

const IRTree::IRTExpression* IRTree::IRTSCjump::GetExpRight() const
{
	return expRight;
}

const IRTree::Label* IRTree::IRTSCjump::GetLabelLeft() const
{
	return labelLeft;
}

const IRTree::Label* IRTree::IRTSCjump::GetLabelRight() const
{
	return labelRight;
}

void IRTree::IRTSCjump::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}
