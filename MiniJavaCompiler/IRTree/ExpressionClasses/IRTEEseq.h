#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IRTEEseq : public IRTExpression {
	public:

		IRTEEseq( const std::shared_ptr<IRTStatement> _stm, const std::shared_ptr<IRTExpression> _exp );

		const std::shared_ptr<IRTStatement> GetStm() const;
		const std::shared_ptr<IRTExpression> GetExp() const;

		void Accept( IVisitor* visitor ) const override;

	private:

		const std::shared_ptr<IRTStatement> stm;
		const std::shared_ptr<IRTExpression> exp;

	};
}
