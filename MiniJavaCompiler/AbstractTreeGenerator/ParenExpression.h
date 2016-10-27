#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CParenExpression : public IExpression {
	public:
		CParenExpression( IExpression* theExpression );
		virtual ~CParenExpression();

		virtual void Accept(IVisitor*) override;
		const std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
