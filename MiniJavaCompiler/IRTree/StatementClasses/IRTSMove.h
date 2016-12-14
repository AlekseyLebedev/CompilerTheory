#pragma once

#include "..\IRTree.h"

namespace IRTree {

	class IRTSMove : public IRTStatement {
	public:
		
		IRTSMove( const IRTExpression* _dst, const IRTExpression* _src );

		const IRTExpression* GetExrDst() const;
		const IRTExpression* GetExrSrc() const;

        void Accept( IRTreeVisitor* visitor ) const override;
        const IRTExpList* children() const override;
		
	private:

		const IRTExpression* dst;
		const IRTExpression* src;

	};
}
