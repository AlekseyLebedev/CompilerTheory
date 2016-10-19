#pragma once
#include <string>

namespace FirstTask {
	class CINTEGER_LITERAL
	{
	public:
		CINTEGER_LITERAL(int theValue);
		CINTEGER_LITERAL(std::string theStringValue);
		virtual ~CINTEGER_LITERAL();
		int GetValue() const;
		std::string GetStringValue() const;
	private:
		int value;
		std::string stringValue;
	};
}
