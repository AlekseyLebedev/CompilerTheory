#pragma once

#include "..\IRTExpression.h"
#include"..\IRTLabel.h"

namespace IRTree {

	class IRTEName : public IRTExpression {
	public:

		IRTEName( const std::shared_ptr<Label> _label );

		const std::shared_ptr<Label> GetLabel() const;

		void Accept( IVisitor* visitor ) const override;

	private:

		const std::shared_ptr<Label> label;

	};
}
