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
