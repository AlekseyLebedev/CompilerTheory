#pragma once

#include "..\IRTStatement.h"
#include "..\IRTConstants.h"
#include "..\IRTLabel.h"

namespace IRTree {

	class IRTSCjump : public IRTStatement {
	public:
		
		IRTSCjump( const RELOP _relop, std::shared_ptr<IRTExpression> _expLeft, std::shared_ptr<IRTExpression> _expRight,
			std::shared_ptr<Label> _labelLeft, std::shared_ptr<Label> _labelRight );

		const RELOP GetRelop() const;
		const std::shared_ptr<IRTExpression> GetExpLeft() const;
		const std::shared_ptr<IRTExpression> GetExpRight() const;
		const std::shared_ptr<Label> GetLabelLeft() const;
		const std::shared_ptr<Label> GetLabelRight() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const RELOP relop;
		std::shared_ptr<IRTExpression> expLeft;
		std::shared_ptr<IRTExpression> expRight;
		std::shared_ptr<Label> labelLeft;
		std::shared_ptr<Label> labelRight;

	};
}
