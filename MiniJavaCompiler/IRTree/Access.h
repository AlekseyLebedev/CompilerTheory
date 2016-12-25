#pragma once
#include "IVisitor.h"
#include "IRTExpression.h"

namespace IRTree {
	class IAccess : public IRTExpression {
	public:
		IAccess( int name, int type );
		void Accept( IVisitor* visitor ) const override;
		int GetName();
		int GetType();
	private:
		int name;
		int type;
	};
}