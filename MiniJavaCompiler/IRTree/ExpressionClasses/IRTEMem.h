#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IRTEMem : public IRTExpression {
	public:
		
		IRTEMem( IRTExpression* _exp );

		const IRTExpression* GetExp() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const IRTExpression* exp;

	};
}
