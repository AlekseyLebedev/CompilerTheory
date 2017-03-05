#include <string>
#include "Access.h"

IRTree::IAccess::IAccess( int name, int type, int _offset, const std::wstring& _info ) : name( name ), type( type ), info( _info ), offset( _offset )
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

const int IRTree::IAccess::GetOffset() const
{
	return offset;
}

const std::wstring & IRTree::IAccess::GetInfo() const
{
	return info;
}
