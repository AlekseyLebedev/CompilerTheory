#pragma once

#include "IExp.h";

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