#pragma once

#include <memory>
#include "Type.h"
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CArgument : public INode {
	public:
		CArgument( CType* theType, CIdExpression* theIdExpression );
		virtual ~CArgument();

		const std::shared_ptr<CType> GetType() const;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;

		virtual void Accept( IVisitor*v ) override;
	private:
		std::shared_ptr<CType> type;
		std::shared_ptr<CIdExpression> idExpression;
	};
}
