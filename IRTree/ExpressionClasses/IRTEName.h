#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTEName : public IRTExpression {
	public:
		
		IRTEName( const Label* _label );

		Label* GetLabel() const;
		
	private:

		const Label* label;

	};
}
