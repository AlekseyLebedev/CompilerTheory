#pragma once

#include <memory>
#include "IExpression.h"

namespace AbstractTreeGenerator {
	class CListConstructorExpression : public IExpression {
	public:
		CListConstructorExpression( IExpression* theExpression );
		virtual ~CListConstructorExpression();

		virtual void Accept(IVisitor*v) override;
		const std::shared_ptr<IExpression> GetExpression() const;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
