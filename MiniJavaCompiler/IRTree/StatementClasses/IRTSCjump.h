#pragma once

#include "..\IRTStatement.h"
#include "..\IRTConstants.h"
#include "..\IRTLabel.h"

namespace IRTree {

	class IRTSCjump : public IRTStatement {
	public:
		
		IRTSCjump( const RELOP _relop, const std::shared_ptr<IRTExpression> _expLeft, const std::shared_ptr<IRTExpression> _expRight,
			const std::shared_ptr<Label> _labelLeft, const std::shared_ptr<Label> _labelRight );

		const RELOP GetRelop() const;
		const std::shared_ptr<IRTExpression> GetExpLeft() const;
		const std::shared_ptr<IRTExpression> GetExpRight() const;
		const std::shared_ptr<Label> GetLabelLeft() const;
		const std::shared_ptr<Label> GetLabelRight() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const RELOP relop;
		const std::shared_ptr<IRTExpression> expLeft;
		const std::shared_ptr<IRTExpression> expRight;
		const std::shared_ptr<Label> labelLeft;
		const std::shared_ptr<Label> labelRight;

	};
}
