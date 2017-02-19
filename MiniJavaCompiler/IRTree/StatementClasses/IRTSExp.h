#pragma once

#include "..\IRTStatement.h"

namespace IRTree {

	class IRTSExp : public IRTStatement {
	public:
		
		IRTSExp( const std::shared_ptr<IRTExpression> _exp );

		const std::shared_ptr<IRTExpression> GetExp() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const std::shared_ptr<IRTExpression> exp;

	};
}
