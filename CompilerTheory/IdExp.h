#pragma once
#include <string>

namespace FirstTask {
	class IdExp
	{
	public:
		IdExp(std::string _name);
		virtual ~IdExp();

	private:
		std::string name;
	};
}
