#pragma once
#include <string>
#include "INode.h"

namespace AbstractTreeGenerator {
	class CINTEGER_LITERAL  : INode
	{
	public:
		CINTEGER_LITERAL(int theValue);
		CINTEGER_LITERAL(std::string theStringValue);
		virtual ~CINTEGER_LITERAL();
		int GetValue() const;
		std::string GetStringValue() const;
		virtual void Accept( IVisitor * ) override;
	private:
		int value;
		std::string stringValue;

	};
}
