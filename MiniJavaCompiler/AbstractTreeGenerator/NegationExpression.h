#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CNegationExpression : public IExpression {
	public:
		CNegationExpression( IExpression* theExpression );
		virtual ~CNegationExpression();

		virtual void Accept(IVisitor* v) override;
		const std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
