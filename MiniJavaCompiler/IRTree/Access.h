#pragma once
#include "IVisitor.h"
#include "IRTExpression.h"

namespace IRTree {
	class IAccess : public IRTExpression {
	public:
		IAccess( int name, int type );
		void Accept( IVisitor* visitor ) const override;
		const int GetName() const;
		const int GetType() const;
	private:
		const int name;
		const int type;
	};
}