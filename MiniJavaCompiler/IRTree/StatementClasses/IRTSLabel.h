#pragma once

#include "..\IRTreeVisitor.h"

namespace IRTree {

	class IRTSLabel : public IRTStatement {
	public:
		
		IRTSLabel( const Label* _label );

		const Label* GetLabel() const;
		
	private:

		const Label* label;

	};
}
