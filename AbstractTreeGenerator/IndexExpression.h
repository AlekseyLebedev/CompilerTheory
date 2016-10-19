#pragma once
#include "IExpression.h"
#include <memory>


namespace FirstTask {
	class CIndexExpression : public IExpression {
	public:
		CIndexExpression( std::shared_ptr<IExpression> theExpressionFirst,
			std::shared_ptr<IExpression> theExpressionSecond );
		virtual ~CIndexExpression();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IExpression> epressionFirst;
		std::shared_ptr<IExpression> expressionSecond;
	};
}
