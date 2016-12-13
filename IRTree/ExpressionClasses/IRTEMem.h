#pragma once

#include "..\IRTreeVisitor.h"
#include "..\IRTExpression.h"

	namespace IRTree {

		class IRTEMem : public IRTExpression {
		public:
			
			IRTEMem( IRTExpression* _expr );

			const IRTExpression* GetExp() const;
			
		private:

			const IRTExpression* expr;

	};
}
