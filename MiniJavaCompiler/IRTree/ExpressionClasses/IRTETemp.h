#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTETemp : public IRTExpression {
	public:
		
        IRTETemp( const Temp* _temp );

        const Temp* GetTemp() const;

        void Accept( IRTreeVisitor* visitor ) const override;

        const IRTExpList* children() const override;
		
	private:

        const Temp* temp;

	};
}
