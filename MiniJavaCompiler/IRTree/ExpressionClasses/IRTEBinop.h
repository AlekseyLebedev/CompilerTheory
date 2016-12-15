#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTEBinop : public IRTExpression {
	public:
		
		IRTEBinop( RELOP _binop, const IRTExpression* _left, const IRTExpression* _right );

        const RELOP GetBinop() const;
		const IRTExpression* GetLeft() const;
		const IRTExpression* GetRight() const;

        void Accept( IRTreeVisitor* visitor ) const override;
        const IRTExpList* children() const override;
		
	private:

		const RELOP binop;
		const IRTExpression* left;
		const IRTExpression* right;

	};
}
