// TODO: хер знает, может быть следует хранить в качестве value string а не bool, 
// но bool было бы логичнее

#pragma once
#include <string>

namespace AbstractTreeGenerator {
	class CBOOL_LITERAL{
	public:
		CBOOL_LITERAL(std::string theValue);
		CBOOL_LITERAL(bool theValue);
		virtual ~CBOOL_LITERAL();
	private:
		bool value;
	};
}