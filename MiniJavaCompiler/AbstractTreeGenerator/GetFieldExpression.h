#pragma once

#include <memory>
#include "IExpression.h"
#include "IdExpression.h"
#include "ExpressionList.h"

namespace AbstractTreeGenerator {
	class CGetFieldExpression : public IExpression {
	public:
		CGetFieldExpression( std::shared_ptr<IExpression> theExpression,
			std::shared_ptr<CIdExpression> theIdExpression,
			std::shared_ptr<CExpressionList> theExpressionList );
		virtual ~CGetFieldExpression();

		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IExpression> expression;
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<CExpressionList> expressionList;
	};
}