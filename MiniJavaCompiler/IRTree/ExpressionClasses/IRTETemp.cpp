#include <memory>
#include "IRTETemp.h"

IRTree::IRTETemp::IRTETemp( const std::shared_ptr<Temp> _temp ) : temp( _temp )
{
}

const std::shared_ptr<IRTree::Temp> IRTree::IRTETemp::GetTemp() const
{
    return temp;
}

void IRTree::IRTETemp::Accept( IVisitor* visitor ) const
{
	visitor->Visit( this );
}
