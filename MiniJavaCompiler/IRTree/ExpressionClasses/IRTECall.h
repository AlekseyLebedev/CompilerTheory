#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IRTECall : public IRTExpression {
	public:
			
		IRTECall( const IRTExpression* _func, const IRTExpList* _args );

		const IRTExpression* GetFunc() const;
		const IRTExpList* GetArgs() const;

        void Accept( IVisitor* visitor ) const override;
			
	private:

		const IRTExpression* func;
		const IRTExpList* args;

    };
}
