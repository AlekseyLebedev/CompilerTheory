#pragma once

#include "..\IRTStatement.h"

namespace IRTree {

	class IRTSSeq : public IRTStatement {
	public:
		
		IRTSSeq( const std::shared_ptr<IRTStatement> _left, const std::shared_ptr<IRTStatement> _right );

		const std::shared_ptr<IRTStatement> GetStmLeft() const;
		const std::shared_ptr<IRTStatement> GetStmRight() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const std::shared_ptr<IRTStatement> left;
		const std::shared_ptr<IRTStatement> right;

	};
}
