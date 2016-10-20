#pragma once
#include "IExpression.h"
#include <memory>
#include "INode.h"
#include "ExpressionList.h"

namespace AbstractTreeGenerator {
	class CExpressionList : public INode
	{
	public:
		CExpressionList( IExpression* theExpression,
			CExpressionList* theExpressionList = nullptr );
		virtual ~CExpressionList();

		virtual void Accept(IVisitor*v) override;
		const std::shared_ptr<IExpression> GetExpression() const;
		const std::shared_ptr<CExpressionList> GetExpressionList() const;
	private:
		std::shared_ptr<IExpression> expression;
		std::shared_ptr<CExpressionList> expressionList;
	};
}
