#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IRTEMem : public IRTExpression {
	public:
		
		IRTEMem( std::shared_ptr<IRTExpression> _exp );

		const std::shared_ptr<IRTExpression> GetExp() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const std::shared_ptr<IRTExpression> exp;

	};
}
