#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTEMem : public IRTExpression {
	public:
		
		IRTEMem( IRTExpression* _exp );

		const IRTExpression* GetExp() const;

        void Accept( IRTreeVisitor* visitor ) const override;
		
	private:

		const IRTExpression* exp;

	};
}
