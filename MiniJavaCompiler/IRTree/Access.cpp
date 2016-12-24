#include "Access.h"

IRTree::IAccess::IAccess( int name ) : name(name)
{
}

void IRTree::IAccess::Accept( IVisitor * visitor )
{
	/*visitor->Visit( this );*/
}
