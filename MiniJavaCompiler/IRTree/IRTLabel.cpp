#include "IRTLabel.h"

IRTree::Label::Label( const std::string _name ) : name( _name )
{
}

const std::string IRTree::Label::GetName() const
{
    return name;
}
