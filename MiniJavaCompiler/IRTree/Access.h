#pragma once
#include "IVisitor.h"
#include "IRTStatement.h"

namespace IRTree {
	class IAccess : INode {
	public:
		IAccess( int name );
		virtual void Accept( IVisitor* visitor ) override;
	private:
		int name;
	};
}