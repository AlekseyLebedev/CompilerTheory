#pragma once

#include <memory>
#include "IdExpression.h"
#include "INode.h"

namespace AbstractTreeGenerator {
	class IType : public INode {

	};

	enum TStandardType {
		ST_Int, ST_Bool, ST_Intlist
	};

	class CBasicType : public IType {
	public:
		CBasicType( TStandardType );
		virtual ~CBasicType() {};

		virtual void Accept( IVisitor* v ) override;
		TStandardType GetValue() const;
	private:
		TStandardType value;
	};

	class CIdType : public IType {
	public:
		CIdType( CIdExpression* theIdExpression );
		virtual ~CIdType() {}

		virtual void Accept( IVisitor* v ) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};


}
