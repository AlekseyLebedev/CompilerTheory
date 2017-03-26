#include "IRTEConst.h"

IRTree::IRTEConst::IRTEConst( int _value ) : value( _value )
{
}

int IRTree::IRTEConst::GetValue() const
{
	return value;
}

void IRTree::IRTEConst::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}

int IRTree::IRTEConst::GetValueAsInt()
{
	return GetValue();
}

IRTree::IRTEConstBool::IRTEConstBool( bool _value ) : value(_value)
{
}

bool IRTree::IRTEConstBool::GetValue() const
{
	return value;
}

void IRTree::IRTEConstBool::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}

int IRTree::IRTEConstBool::GetValueAsInt()
{
	return (int)GetValue();
}
