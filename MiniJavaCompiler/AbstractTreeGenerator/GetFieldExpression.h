#pragma once

#include <memory>
#include "IExpression.h"
#include "IdExpression.h"
#include "ExpressionList.h"

namespace AbstractTreeGenerator {
	class CGetFieldExpression : public IExpression {
	public:
		CGetFieldExpression( IExpression* theExpression,
			CIdExpression* theIdExpression,
			CExpressionList* theExpressionList );
		virtual ~CGetFieldExpression();

		virtual void Accept(IVisitor*) override;
		const std::shared_ptr<IExpression> GetExpression() const;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
		const std::shared_ptr<CExpressionList> GetExpressionList() const;
	private:
		std::shared_ptr<IExpression> expression;
		std::shared_ptr<CIdExpression> idExpression;
		std::shared_ptr<CExpressionList> expressionList;
	};
}
