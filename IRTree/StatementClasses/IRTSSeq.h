#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTSSeq : public IRTStatement {
	public:
		
		IRTSSeq( const IRTStatement* _left, const IRTStatement* _right );

		const IRTStatement* GetStmLeft() const;
		const IRTStatement* GetStmLeft() const;
		
	private:

		const IRTStatement* left;
		const IRTStatement* right;

	};
}
