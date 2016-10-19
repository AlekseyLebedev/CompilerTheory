#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CNegationExpression : public IExpression {
	public:
		CNegationExpression( std::shared_ptr<IExpression> theExpression );
		virtual ~CNegationExpression();

		virtual void Accept(IVisitor* v) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
