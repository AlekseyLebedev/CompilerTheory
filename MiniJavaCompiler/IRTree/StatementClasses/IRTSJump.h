#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTSJump : public IRTStatement {
	public:
		
		IRTSJump( const Label* _label );

		const Label* GetLabel() const;

        void Accept( IRTreeVisitor* visitor ) const override;
		
	private:

		const Label* label;

	};
}
