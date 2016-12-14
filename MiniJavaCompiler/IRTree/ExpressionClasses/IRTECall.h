#pragma once

#include "..\IRTree.h"

namespace IRTree {

	class IRTECall : public IRTExpression {
	public:
			
		IRTECall( const IRTExpression* _func, const IRTExpList* _args );

		const IRTExpression* GetExp() const;
		const IRTExpList* GetExpList() const;

        void Accept( IRTreeVisitor* visitor ) const override;
        const IRTExpList* children() const override;
			
	private:

		const IRTExpression* func;
		const IRTExpList* args;

    };
}
