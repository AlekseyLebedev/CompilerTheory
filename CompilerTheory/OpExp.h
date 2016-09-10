#pragma once

#include "stdafx.h";
#include "IExp.h";

namespace FirstTask {
	struct COpExp : public IExp {
	public:
		enum TOperationType {
			Plus,
			Minus,
			Times,
			Divide
		};

		COpExp(std::shared_ptr<IExp> left, std::shared_ptr<IExp> right, TOperationType type);
		virtual ~COpExp();
		std::shared_ptr<IExp> GetLeftOperand() const;
		std::shared_ptr<IExp> GetRightOperand() const;
		TOperationType GetOperationType() const;

	private:
		std::shared_ptr<IExp> leftOperand, rightOperand;
		TOperationType operation;

	};
}