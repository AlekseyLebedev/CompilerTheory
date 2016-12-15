#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTSMove : public IRTStatement {
	public:
		
		IRTSMove( const IRTExpression* _dst, const IRTExpression* _src );

		const IRTExpression* GetExrDst() const;
		const IRTExpression* GetExrSrc() const;

        void Accept( IRTreeVisitor* visitor ) const override;
		
	private:

		const IRTExpression* dst;
		const IRTExpression* src;

	};
}
