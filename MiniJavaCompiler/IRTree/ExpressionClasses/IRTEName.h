#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTEName : public IRTExpression {
	public:
		
		IRTEName( const Label* _label );

		const Label* GetLabel() const;

        void Accept( IRTreeVisitor* visitor ) const override;
		
	private:

		const Label* label;

	};
}
