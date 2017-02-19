#pragma once

#include "..\IRTExpression.h"
#include "..\IRTTemp.h"

namespace IRTree {

	class IRTETemp : public IRTExpression {
	public:
		
        IRTETemp( const std::shared_ptr<Temp> _temp );

        const std::shared_ptr<Temp> GetTemp() const;

        void Accept( IVisitor* visitor ) const override;
		
	private:

        const std::shared_ptr<Temp> temp;

	};
}
