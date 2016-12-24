#pragma once
#include "IVisitor.h"
#include "IRTStatement.h"

namespace IRTree {
	class IAccess : INode {
	public:
		IAccess( int name );
		void Accept( IVisitor* visitor ) const override;
	private:
		int name;
	};
}