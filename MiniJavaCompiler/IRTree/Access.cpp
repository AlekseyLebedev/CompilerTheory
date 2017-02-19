#include <string>
#include "Access.h"

IRTree::IAccess::IAccess( int name, int type, const std::wstring& _info ) : name( name ), type( type ), info( _info )
{
}

void IRTree::IAccess::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}

const int IRTree::IAccess::GetName() const
{
	return name;
}

const int IRTree::IAccess::GetType() const
{
	return type;
}

const std::wstring & IRTree::IAccess::GetInfo() const
{
	return info;
}
