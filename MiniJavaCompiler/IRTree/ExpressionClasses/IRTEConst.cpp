#include "IRTEConst.h"

IRTree::IRTEConst::IRTEConst( unsigned int _value ) : value( _value )
{
}

unsigned int IRTree::IRTEConst::GetValue() const
{
	return value;
}

void IRTree::IRTEConst::Accept( IRTreeVisitor* visitor ) const
{
	visitor->Visit( this );
}
