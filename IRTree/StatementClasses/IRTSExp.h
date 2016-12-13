#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTSExp : public IRTStatement {
	public:
		
		IRTSExp( const IRTExression* _exp );

		const IRTExpression* GetExp() const;
		
	private:

		const IRTExpression* exp;

	};
}
