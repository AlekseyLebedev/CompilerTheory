#pragma once

#include <string>

//TO DO
namespace IRTree {

	class Label {
	public:

		Label();
		Label( const int _name );

		const int GetName() const;

	private:

		static int counter;
		int name;
	};
}
