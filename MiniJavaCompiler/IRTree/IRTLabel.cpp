#include "IRTLabel.h"

namespace IRTree {
	Label::Label() : name( counter++ )
	{
	}

	Label::Label( const int _name ) : name( _name )
	{
	}

	const int Label::GetName() const
	{
		return name;
	}

	int Label::counter = 0;
}