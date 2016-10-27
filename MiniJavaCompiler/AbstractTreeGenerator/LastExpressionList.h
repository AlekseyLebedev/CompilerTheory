#pragma once

#include "IExpression.h"
#include <memory>

namespace AbstractTreeGenerator {
	class CLastExpressionList : public IExpression {
	public:
		CLastExpressionList(IExpression* _exp);
		virtual ~CLastExpressionList();
		virtual void Accept(IVisitor* v) override;
		std::shared_ptr<IExpression> GetExpression() const; 
		const std::shared_ptr<IExpression> GetExp() const;
	private:
		std::shared_ptr<IExpression> exp;
	};
}
