#include "Access.h"

IRTree::IAccess::IAccess( int name, int type ) : name(name), type(type)
{
}

void IRTree::IAccess::Accept( IVisitor * visitor ) const
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
