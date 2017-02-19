#include "IRTLabel.h"

namespace IRTree {
	Label::Label() : Label( counter++, L"" )
	{
	}

	Label::Label( const int _name, const std::wstring& _info ) : name( _name ), info( _info )
	{
	}

	const int Label::GetName() const
	{
		return name;
	}

	const std::wstring & Label::GetInfo() const
	{
		return info;
	}

	int Label::counter = TStandadLabel::SL_Count;
}