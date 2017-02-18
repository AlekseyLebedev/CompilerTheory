#include "Frame.h"
#include "IRTExpression.h"
#include "IRTLabel.h"
#include <memory>

namespace IRTree {

	CFrame::CFrame( int className, Label* _label ) : className( className ), label( _label ), thisAccess( new IAccess( ThisName, className ) )
	{
	}

	void CFrame::InsertVariable( int name, std::shared_ptr<IAccess> access )
	{
		variables.insert( std::pair<int, std::shared_ptr<IAccess>>( name, access ) );
	}

	std::shared_ptr<IAccess> CFrame::GetDataInfo( int name )
	{
		return variables.find( name )->second;
	}

	std::shared_ptr<Label> CFrame::GetLabel()
	{
		return label;
	}

	std::shared_ptr<IAccess> CFrame::GetThisAccess()
	{
		return thisAccess;
	}

	const int CFrame::ThisName = -11;
}