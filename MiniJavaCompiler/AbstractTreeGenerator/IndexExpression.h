#pragma once
#include "IExpression.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CIndexExpression : public IExpression {
	public:
		CIndexExpression( IExpression* theExpressionFirst,
			IExpression* theExpressionSecond );
		virtual ~CIndexExpression();

		virtual void Accept( IVisitor* ) override;
		const std::shared_ptr<IExpression> GetEpressionFirst() const;
		const std::shared_ptr<IExpression> GetExpressionSecond() const;
	private:
		std::shared_ptr<IExpression> epressionFirst;
		std::shared_ptr<IExpression> expressionSecond;
	};
}
