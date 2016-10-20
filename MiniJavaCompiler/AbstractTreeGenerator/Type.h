#pragma once

#include <memory>
#include "IdExpression.h"
#include "INode.h"

namespace AbstractTreeGenerator {
	class CType : public INode {
	public:
		CType( const char* theIdExpression );
		virtual ~CType();

		virtual void Accept(IVisitor* v) override;
	private:
		const char* idExpression;
	};
}
