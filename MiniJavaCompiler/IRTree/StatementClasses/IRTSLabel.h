#pragma once

#include "..\IRTStatement.h"
#include "..\IRTLabel.h"

namespace IRTree {

	class IRTSLabel : public IRTStatement {
	public:

		IRTSLabel( const std::shared_ptr<Label> _label );

		const std::shared_ptr<Label> GetLabel() const;

		void Accept( IVisitor* visitor ) const override;

	private:

		const std::shared_ptr<Label> label;

	};
}
