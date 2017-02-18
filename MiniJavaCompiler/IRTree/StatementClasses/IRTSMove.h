#pragma once

#include "..\IRTStatement.h"

namespace IRTree {

	class IRTSMove : public IRTStatement {
	public:
		
		IRTSMove( const std::shared_ptr<IRTExpression> _dst, const std::shared_ptr<IRTExpression> _src );

		const std::shared_ptr<IRTExpression> GetExrDst() const;
		const std::shared_ptr<IRTExpression> GetExrSrc() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const std::shared_ptr<IRTExpression> dst;
		const std::shared_ptr<IRTExpression> src;

	};
}
