#pragma once

#include "..\IRTExpression.h"

namespace IRTree {

	class IConst : public IRTExpression {
	public:
		virtual int GetValueAsInt() = 0;
	};

	class IRTEConst : public IConst {
	public:

		IRTEConst(int _value);

		int GetValue() const;

        void Accept( IVisitor* visitor ) const override;

		virtual int GetValueAsInt() override;
	private:

		const int value;

	};

	class IRTEConstBool : public IConst {
	public:

		IRTEConstBool( bool _value );

		bool GetValue() const;

		void Accept( IVisitor* visitor ) const override;

		virtual int GetValueAsInt() override;
	private:

		const bool value;
	};
}
