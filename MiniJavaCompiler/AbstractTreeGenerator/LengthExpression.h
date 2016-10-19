#pragma once
#include "IExpression.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CLengthExpression : public IExpression {
	public:
		CLengthExpression( std::shared_ptr<IExpression> theExpression );
		virtual ~CLengthExpression();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
