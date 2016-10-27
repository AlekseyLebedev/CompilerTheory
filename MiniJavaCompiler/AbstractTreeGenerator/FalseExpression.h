#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CFalseExpression : public IExpression {
	public:
		CFalseExpression();
		virtual ~CFalseExpression();

		virtual void Accept(IVisitor*) override;
	};
}
