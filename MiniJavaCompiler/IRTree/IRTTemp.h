#pragma once

#include <string>

// TO DO
namespace IRTree {

    class Temp
    {
    public:
		Temp( int _name );
        const int GetName() const;

    private:

        const int name;
    };
}
