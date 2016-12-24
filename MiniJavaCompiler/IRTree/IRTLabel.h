#pragma once

#include <string>

//TO DO
namespace IRTree {

    class Label
    {
    public:

        Label();
        Label( const std::string _name );

        const std::string GetName() const;

    private:

        const std::string name;
    };
}
