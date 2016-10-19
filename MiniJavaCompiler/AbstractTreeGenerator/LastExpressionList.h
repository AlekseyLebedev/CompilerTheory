#pragma once

#include "IExpression.h"
#include <memory>

namespace AbstractTreeGenerator {
	class CLastExpressionList : public IExpression {
	public:
		CLastExpressionList(std::shared_ptr<IExpression> _exp);
		virtual ~CLastExpressionList();
		virtual void Accept(IVisitor* v) override;
		std::shared_ptr<IExpression> GetExpression() const; 
	private:
		std::shared_ptr<IExpression> exp;
	};
}
