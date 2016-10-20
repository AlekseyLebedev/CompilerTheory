#pragma once

#include "IExpression.h"
#include <memory>

namespace AbstractTreeGenerator {
	class COperationExpression : public IExpression {
	public:
		enum TOperationType {
			Plus,
			Minus,
			Times,
			Divide,
			And,
			Less,
			Mod,
			Or
		};

		COperationExpression(std::shared_ptr<IExpression> left, std::shared_ptr<IExpression> right, TOperationType type);
		virtual ~COperationExpression();
		virtual void Accept(IVisitor*) override;
		std::shared_ptr<IExpression> GetLeftOperand() const;
		std::shared_ptr<IExpression> GetRightOperand() const;
		TOperationType GetOperationType() const;

	private:
		std::shared_ptr<IExpression> leftOperand, rightOperand;
		TOperationType operation;
	};
}
