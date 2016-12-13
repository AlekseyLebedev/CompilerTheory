#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTSMove : public IRTStatement {
	public:
		
		IRTSMove( const IRTExpression* _dst, const IRTExpression* _src );

		const IRTExpression* GetExrDst() const;
		const IRTExpression* GetExrSrc() const;
		
	private:

		const IRTExpression* dst;
		const IRTExpression* src;

	};
}
