#pragma once

#include <memory>
#include "IExpression.h"

namespace FirstTask {
	class CNegationExpression {
	public:
		CNegationExpression( std::shared_ptr<IExpression> theExpression );
		virtual ~CNegationExpression();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
