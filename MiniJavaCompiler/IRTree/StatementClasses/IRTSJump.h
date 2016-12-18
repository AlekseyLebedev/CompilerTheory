#pragma once

#include "..\IRTStatement.h"
#include "..\IRTLabel.h"

namespace IRTree {

	class IRTSJump : public IRTStatement {
	public:

		IRTSJump( const Label* _label );

		const Label* GetLabel() const;

		void Accept( IVisitor* visitor ) const override;

	private:

		const Label* label;

	};
}
