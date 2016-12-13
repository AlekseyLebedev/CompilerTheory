#pragma once

#include "..\IRTreeVisitor.h"
#include "..\IRTExpression.h"

	namespace IRTree {

		class IRTECall : public IRTExpression {
		public:
			
			IRTECall( const IRTExpression* _func, const IRTExpList* _args );

			const IRTExpression* GetExp() const;
			const IRTExpList* GetExpList() const;
			
		private:

			const IRTExpression* func;
			const IRTExpList* args;

	};
}
