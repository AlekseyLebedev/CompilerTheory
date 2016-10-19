#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CParenExpression : public IExpression {
	public:
		CParenExpression( std::shared_ptr<IExpression> theExpression );
		virtual ~CParenExpression();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}