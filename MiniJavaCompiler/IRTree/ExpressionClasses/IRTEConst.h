#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IRTEConst : public IRTExpression {
	public:

		IRTEConst(int _value);

		int GetValue() const;

        void Accept( IVisitor* visitor ) const override;

	private:

		const int value;

	};

	class IRTEConstBool : public IRTExpression {
	public:

		IRTEConstBool( bool _value );

		bool GetValue() const;

		void Accept( IVisitor* visitor ) const override;

	private:

		const bool value;
	};
}
