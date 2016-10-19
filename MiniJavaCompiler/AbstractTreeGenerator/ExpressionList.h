#pragma once
#include "IExpression.h"
#include <memory>

namespace AbstractTreeGenerator {
	class CExpressionList
	{
	public:
		CExpressionList( std::shared_ptr<IExpression> theExpression );
		virtual ~CExpressionList();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
