#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CThisExpression : public IExpression {
	public:
		CThisExpression();
		virtual ~CThisExpression();

		virtual void Accept(IVisitor*) override;
	private:
	};
}