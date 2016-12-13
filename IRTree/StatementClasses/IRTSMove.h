#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTSMove : public IRTStatement {
	public:
		
		IRTSMove( const IRTExression* _dst, const IRTExression* _src );

		const IRTExression* GetExrDst() const;
		const IRTExression* GetExrSrc() const;
		
	private:

		const IRTExression* dst;
		const IRTStatement* src;

	};
}
