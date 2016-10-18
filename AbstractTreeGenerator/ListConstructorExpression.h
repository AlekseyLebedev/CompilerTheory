#pragma once

#include <memory>
#include "IExpression.h"

namespace FirstTask {
	class CListConstructorExpression {
	public:
		CListConstructorExpression( std::shared_ptr<IExpression> theExpression );
		virtual ~CListConstructorExpression();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
