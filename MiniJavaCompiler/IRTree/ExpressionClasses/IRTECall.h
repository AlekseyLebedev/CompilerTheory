#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IRTECall : public IRTExpression {
	public:
			
		IRTECall( const std::shared_ptr<IRTExpression> _func, const std::shared_ptr<IRTExpList> _args );

		const std::shared_ptr<IRTExpression> GetFunc() const;
		const std::shared_ptr<IRTExpList> GetArgs() const;

        void Accept( IVisitor* visitor ) const override;
			
	private:

		const std::shared_ptr<IRTExpression> func;
		const std::shared_ptr<IRTExpList> args;

    };
}
