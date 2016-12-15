#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTSExp : public IRTStatement {
	public:
		
		IRTSExp( const IRTExpression* _exp );

		const IRTExpression* GetExp() const;

        void Accept( IRTreeVisitor* visitor ) const override;
		
	private:

		const IRTExpression* exp;

	};
}
