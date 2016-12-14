#pragma once

#include "..\IRTree.h"

namespace IRTree {

	class IRTSExp : public IRTStatement {
	public:
		
		IRTSExp( const IRTExpression* _exp );

		const IRTExpression* GetExp() const;

        void Accept( IRTreeVisitor* visitor ) const override;
        const IRTExpList* children() const override;
		
	private:

		const IRTExpression* exp;

	};
}
