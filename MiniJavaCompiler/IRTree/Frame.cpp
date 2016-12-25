#include "Frame.h"
#include "IRTExpression.h"
#include "IRTLabel.h"
#include <memory>

namespace IRTree {

	CFrame::CFrame( int className, Label* _label ) : className( className ), label( _label ), thisAccess( new IAccess( ThisName, className ) )
	{
	}

	void CFrame::InsertVariable( int name, IAccess* access )
	{
		variables.insert( std::pair<int, IAccess*>( name, access ) );
	}

	IAccess* CFrame::GetDataInfo( int name )
	{
		return variables.find( name )->second;
	}

	Label * CFrame::GetLabel()
	{
		return label;
	}

	IAccess * CFrame::GetThisAccess()
	{
		return thisAccess;
	}

	const int CFrame::ThisName = -11;
}