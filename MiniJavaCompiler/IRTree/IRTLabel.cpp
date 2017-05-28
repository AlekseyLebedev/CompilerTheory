#include <cassert>
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

	std::wstring Label::GetAssmeblerName()
	{
		if( name < 0 ) {
			return L"lbln" + std::to_wstring( -name ) + L"_" + info;
		} else {
			std::wstring suffix;
			switch( name ) {
				case 0:
					assert( false );
					break;
				case 1:
					suffix = L"_alloc";
					break;
				case 2:
					suffix = L"_println";
					break;
				default:
					break;
			}
			return L"lblp" + std::to_wstring( name );
		}
	}

	int Label::counter = TStandadLabel::SL_Count;
}