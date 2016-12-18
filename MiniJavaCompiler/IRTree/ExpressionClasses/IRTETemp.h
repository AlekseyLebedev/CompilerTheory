#pragma once

#include "..\IRTExpression.h"
#include "..\IRTTemp.h"

namespace IRTree {

	class IRTETemp : public IRTExpression {
	public:
		
        IRTETemp( const Temp* _temp );

        const Temp* GetTemp() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

        const Temp* temp;

	};
}
