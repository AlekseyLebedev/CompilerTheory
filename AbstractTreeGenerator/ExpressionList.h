#pragma once
#include "IExpression.h"
#include <memory>

namespace FirstTask {
	class CExpressionList
	{
	public:
		CExpressionList( std::shared_ptr<IExpression> theExpression );
		virtual ~CExpressionList();

//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
