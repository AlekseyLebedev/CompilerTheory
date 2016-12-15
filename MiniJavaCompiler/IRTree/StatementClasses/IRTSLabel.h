#pragma once

#include "..\IRTreeClasses.h"

namespace IRTree {

	class IRTSLabel : public IRTStatement {
	public:
		
		IRTSLabel( const Label* _label );

		const Label* GetLabel() const;

        void Accept( IRTreeVisitor* visitor ) const override;
		
	private:

		const Label* label;

	};
}
