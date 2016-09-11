#pragma once

#include "stdafx.h"
#include "IExpression.h"

namespace FirstTask {
	struct COpExp : public IExpression {
	public:
		enum TOperationType {
			Plus,
			Minus,
			Times,
			Divide
		};

		COpExp(std::shared_ptr<IExpression> left, std::shared_ptr<IExpression> right, TOperationType type);
		virtual ~COpExp();
		std::shared_ptr<IExpression> GetLeftOperand() const;
		std::shared_ptr<IExpression> GetRightOperand() const;
		TOperationType GetOperationType() const;

	private:
		std::shared_ptr<IExpression> leftOperand, rightOperand;
		TOperationType operation;

	};
}