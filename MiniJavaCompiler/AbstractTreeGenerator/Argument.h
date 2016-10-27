#pragma once

#include <memory>
#include "Type.h"
#include "IdExpression.h"

namespace AbstractTreeGenerator {
	class CArgument : public INode {
	public:
		CArgument( IType* theType, CIdExpression* theIdExpression );
		virtual ~CArgument();

		const std::shared_ptr<IType> GetType() const;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;

		virtual void Accept( IVisitor*v ) override;
	private:
		std::shared_ptr<IType> type;
		std::shared_ptr<CIdExpression> idExpression;
	};
}
