#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTEConst : public IRTExpression {
	public:

		IRTEConst(unsigned int _value);

		unsigned int GetValue() const;

        void Accept( IRTreeVisitor* visitor ) const override;
        const IRTExpList* children() const override;

	private:

		const unsigned int value;

	};
}
