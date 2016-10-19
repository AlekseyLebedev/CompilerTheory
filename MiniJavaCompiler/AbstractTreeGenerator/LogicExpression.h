#pragma once
#include "IExpression.h"
#include "BOOL_LITERAL.h"
#include <memory>

namespace AbstractTreeGenerator {
	class CLogicExpression : public IExpression {
	public:
		CLogicExpression(std::shared_ptr<CBOOL_LITERAL> theValue);
		~CLogicExpression();
	private:
		std::shared_ptr<CBOOL_LITERAL> value;
	};
}