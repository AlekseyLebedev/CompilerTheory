#include "IRTSLabel.h"

IRTree::IRTSLabel::IRTSLabel( const Label* label ) : label( _label )
{
}

const IRTree::Label* IRTree::IRTSLabel::GetLabel() const
{
	return label;
}

void IRTree::IRTSLabel::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}

const IRTree::IRTExpList* IRTree::IRTSLabel::children() const
{
	//TO DO
	return nullptr;
}
