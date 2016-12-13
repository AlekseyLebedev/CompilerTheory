#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTSJump : public IRTStatement {
	public:
		
		IRTSJump( const IRTExression* _exp, const Label* _label );

		const IRTExpression* GetExp() const;
		const Label* GetLabel() const;
		
	private:

		const IRTExpression* exp;
		const Label* label;

	};
}
