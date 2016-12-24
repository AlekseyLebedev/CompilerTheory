#include "Frame.h"
#include "IRTExpression.h"
#include <memory>
using namespace IRTree;

void CFrame::InsertVariable( int name, IAccess* access)
{
	variables.insert( std::pair<int, IAccess*>(name, access) );
}

IAccess* CFrame::GetDataInfo( int name )
{
	return variables.find( name )->second;
}