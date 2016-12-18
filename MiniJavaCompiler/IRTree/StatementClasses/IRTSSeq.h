#pragma once

#include "..\IRTStatement.h"

namespace IRTree {

	class IRTSSeq : public IRTStatement {
	public:
		
		IRTSSeq( const IRTStatement* _left, const IRTStatement* _right );

		const IRTStatement* GetStmLeft() const;
		const IRTStatement* GetStmRight() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const IRTStatement* left;
		const IRTStatement* right;

	};
}
