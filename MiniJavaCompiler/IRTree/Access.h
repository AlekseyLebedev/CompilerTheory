#pragma once
#include "IVisitor.h"
#include "IRTExpression.h"

namespace IRTree {
	class IAccess : public IRTExpression {
	public:
		IAccess( int name );
		void Accept( IVisitor* visitor ) const override;
	private:
		int name;
	};
}