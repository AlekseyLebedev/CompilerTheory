// хер знает, может быть следует хранить в качестве value string а не bool
#pragma once
#include <string>

namespace FirstTask {
	class CBOOL_LITERAL{
	public:
		CBOOL_LITERAL(std::string theValue);
		CBOOL_LITERAL(bool theValue);
		virtual ~CBOOL_LITERAL();
	private:
		bool value;
	};
}