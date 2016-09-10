#pragma once

#include "IExp.h";

namespace FirstTask {
	struct COpExp : public IExp {
		IExp* LeftOperand;
		IExp* RightOperand;
		enum TOperationType {
			Plus,
			Minus,
			Times,
			Divide
		} operation;

	};
}