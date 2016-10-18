#pragma once
#include "IExpression.h"
#include <memory>


namespace FirstTask {
	class CLengthExpression : public IExpression {
	public:
		CLengthExpression( std::shared_ptr<IExpression> theExpression );
		virtual ~CLengthExpression();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
