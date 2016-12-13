#pragma once

#include "..\IRTreeVisitor.h"
#include "..\IRTExpression.h"

	namespace IRTree {

		class IRTEBinop : public IRTExpression {
		public:
			
			IRTEBinop( TBinop _binop, const IRTExpression* _left, const IRTExpression* _right );

			const IRTExpression* GetLeft() const;
			const IRTExpression* GetRight() const;
			
		private:

			const TBinop binop;
			const IRTExpression* left;
			const IRTExpression* right;

	};
}
