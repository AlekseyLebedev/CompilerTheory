#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTETemp : public IRTExpression {
	public:
		
		//TO DO

        void Accept( IRTreeVisitor* visitor ) const override;

        const IRTExpList* children() const override;
		
	private:

		//TO DO

	};
}
