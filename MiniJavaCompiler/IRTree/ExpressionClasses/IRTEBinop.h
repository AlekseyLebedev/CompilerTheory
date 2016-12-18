#pragma once

#include "..\IRTExpression.h"
#include "..\IRTConstants.h"

namespace IRTree {

	class IRTEBinop : public IRTExpression {
	public:
		
		IRTEBinop( RELOP _binop, const IRTExpression* _left, const IRTExpression* _right );

        const RELOP GetBinop() const;
		const IRTExpression* GetLeft() const;
		const IRTExpression* GetRight() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const RELOP binop;
		const IRTExpression* left;
		const IRTExpression* right;

	};
}
