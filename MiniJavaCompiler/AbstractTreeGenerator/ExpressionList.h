#pragma once
#include "IExpression.h"
#include <memory>
#include "INode.h"

namespace AbstractTreeGenerator {
	class CExpressionList  : public INode
	{
	public:
		CExpressionList( std::shared_ptr<IExpression> theExpression );
		virtual ~CExpressionList();

		virtual void Accept(IVisitor*v) override;
	private:
		std::shared_ptr<IExpression> expression;
	};
}
