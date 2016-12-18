#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IRTEEseq : public IRTExpression {
	public:
		
		IRTEEseq( const IRTStatement* _stm, const IRTExpression* _exp );

		const IRTStatement* GetStm() const;
		const IRTExpression* GetExp() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const IRTStatement* stm;
		const IRTExpression* exp;

	};
}
