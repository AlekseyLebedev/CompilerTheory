#pragma once
#include "IExpression.h"
#include <memory>
#include "INode.h"
#include "ExpressionList.h"

namespace AbstractTreeGenerator {
	class CExpressionList : public INode
	{
	public:
		CExpressionList( std::shared_ptr<IExpression> theExpression,
			std::shared_ptr<CExpressionList> theExpressionList = nullptr );
		virtual ~CExpressionList();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<IExpression> expression;
		std::shared_ptr<CExpressionList> expressionList;
	};
}
