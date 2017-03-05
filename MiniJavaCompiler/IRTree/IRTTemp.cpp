#include "IRTTemp.h"

IRTree::Temp::Temp( int _name ) : name(_name)
{
}

const int IRTree::Temp::GetName() const
{
    return name;
}
