#pragma once
#include "IExpression.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CLengthExpression : public IExpression {
	public:
		CLengthExpression( IExpression* theExpression );
		virtual ~CLengthExpression();

		virtual void Accept(IVisitor*v) override;
		const std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
