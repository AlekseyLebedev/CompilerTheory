#pragma once

#include <memory>
#include "..\IRTExpression.h"
#include "..\IRTConstants.h"

namespace IRTree {

	class IRTEBinop : public IRTExpression {
	public:
		
		IRTEBinop( RELOP _binop, const std::shared_ptr<IRTExpression> _left, const std::shared_ptr<IRTExpression> _right );

        const RELOP GetBinop() const;
		const std::shared_ptr<IRTExpression> GetLeft() const;
		const std::shared_ptr<IRTExpression> GetRight() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const RELOP binop;
		const std::shared_ptr<IRTExpression> left;
		const std::shared_ptr<IRTExpression> right;

	};
}
