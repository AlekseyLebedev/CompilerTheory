#include "IRTLabel.h"

// Временно
// Исправить (то есть убрать, добавив генерацию имён)
IRTree::Label::Label() : name( "abracadabra" )
{
}

IRTree::Label::Label( const std::string _name ) : name( _name )
{
}

const std::string IRTree::Label::GetName() const
{
    return name;
}
