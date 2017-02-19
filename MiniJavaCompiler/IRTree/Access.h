#pragma once
#include "IVisitor.h"
#include "IRTExpression.h"

namespace IRTree {
	class IAccess : public IRTExpression {
	public:
		IAccess( int name, int type, const std::wstring& info = L"" );
		void Accept( IVisitor* visitor ) const override;
		const int GetName() const;
		const int GetType() const;
		const std::wstring& GetInfo() const;
	private:
		const int name;
		const int type;
		const std::wstring& info;
	};
}