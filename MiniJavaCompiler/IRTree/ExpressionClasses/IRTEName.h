#pragma once

#include "..\IRTExpression.h"
#include"..\IRTLabel.h"

namespace IRTree {

	class IRTEName : public IRTExpression {
	public:

		IRTEName( const Label* _label );

		const Label* GetLabel() const;

		void Accept( IVisitor* visitor ) const override;

	private:

		const Label* label;

	};
}
