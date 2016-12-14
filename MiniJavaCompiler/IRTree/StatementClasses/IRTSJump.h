#pragma once

#include "..\IRTree.h"

namespace IRTree {

	class IRTSJump : public IRTStatement {
	public:
		
		IRTSJump( const IRTExpression* _exp, const Label* _label );

		const IRTExpression* GetExp() const;
		const Label* GetLabel() const;

        void Accept( IRTreeVisitor* visitor ) const override;
        const IRTExpList* children() const override;
		
	private:

		const IRTExpression* exp;
		const Label* label;

	};
}
