#pragma once

#include "..\IRTStatement.h"

namespace IRTree {

	class IRTSExp : public IRTStatement {
	public:
		
		IRTSExp( const IRTExpression* _exp );

		const IRTExpression* GetExp() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

		const IRTExpression* exp;

	};
}
