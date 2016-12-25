#include "Access.h"

IRTree::IAccess::IAccess( int name, int type ) : name(name), type(type)
{
}

void IRTree::IAccess::Accept( IVisitor * visitor ) const
{
	//visitor->Visit( this );
}

int IRTree::IAccess::GetName()
{
	return name;
}

int IRTree::IAccess::GetType()
{
	return type;
}
