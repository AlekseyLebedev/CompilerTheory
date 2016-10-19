#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CListConstructorExpression : public IExpression {
	public:
		CListConstructorExpression( std::shared_ptr<IExpression> theExpression );
		virtual ~CListConstructorExpression();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
