#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTEConst : public IRTExpression {
	public:

		IRTEConst(unsigned int _value);

		unsigned int GetValue() const;

	private:

		const unsigned int value;

	};
}
