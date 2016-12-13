#include "IRTSCjump.h"

IRTree::IRTSCjump::IRTSCjump( const RELOP _relop, const IRTExpression* _expLeft, const IRTExpression* _expRight
	const Label _labelLeft, const Label _labelRight )
	: relop( _relop ), expLeft( _expLeft ), exptRight( _expRight ), labelLeft( _labelLeft ), labelRight( _labelRight )
{
}

const IRTree::RELOP* IRTree::IRTSCjump::GetRelop() const
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

const IRTree::Label* IRTree::IRTSCjump::GetRelop() const
{
	return labelLeft;
}

const IRTree::Label* IRTree::IRTSCjump::GetRelop() const
{
	return labelRight;
}

void IRTree::IRTSCjump::Accept( IIRTreeVisitor *visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSCjump::children() const
{
	//TO DO
	return nullptr;
}
