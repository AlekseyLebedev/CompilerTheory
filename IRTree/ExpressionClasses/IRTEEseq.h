#pragma once

#include "..\IRTreeVisitor.h"
#include "..\IRTExpression.h"
#include "..\IRTStatement.h"

	namespace IRTree {

		class IRTEEseq : public IRTExpression {
		public:
			
			IRTEEseq( const IRTStatement* _stm, const IRTExpression* _exp );

			const IRTStatement* GetStm() const;
			const IRTExpression* GetExp() const;
			
		private:

			const IRTStatement* stm;
			const IRTExpression* exp;

	};
}
