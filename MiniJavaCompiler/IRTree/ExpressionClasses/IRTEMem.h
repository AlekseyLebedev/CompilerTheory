#pragma once

#include "..\IRTree.h"

namespace IRTree {

	class IRTEMem : public IRTExpression {
	public:
		
		IRTEMem( IRTExpression* _exp );

		const IRTExpression* GetExp() const;

        void Accept( IRTreeVisitor* visitor ) const override;
        const IRTExpList* children() const override;
		
	private:

		const IRTExpression* exp;

	};
}
