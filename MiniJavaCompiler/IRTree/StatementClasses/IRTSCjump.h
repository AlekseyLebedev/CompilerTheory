#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTSCjump : public IRTStatement {
	public:
		
		IRTSCjump( const RELOP _relop, const IRTExpression* _expLeft, const IRTExpression* _expRight
			const Label _labelLeft, const Label _labelRight );

		const RELOP GetRelop() const;
		const IRTExpression* GetExpLeft() const;
		const IRTExpression* GetExpRight() const;
		const Label* GetLabelLeft() const;
		const Label* GetLabelRight() const;
		
	private:

		const RELOP relop;
		const IRTExpression* expLeft;
		const IRTExpression* expRight;
		const Label* leftLabel;
		const Label* rightLabel;

	};
}
