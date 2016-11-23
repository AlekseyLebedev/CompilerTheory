#pragma once

#include <memory>
#include "IdExpression.h"
#include "INode.h"

namespace AbstractTreeGenerator {
	class IType : public INode {
	public:
		virtual std::string GetType() const = 0;
	};

	enum TStandardType {
		ST_Int, ST_Bool, ST_Intlist
	};

	class CBasicType : public IType {
	public:
		CBasicType( TStandardType );
		virtual ~CBasicType() {};
		virtual std::string GetType() const override;
		virtual void Accept( IVisitor* v ) override;
		TStandardType GetValue() const;
	private:
		TStandardType value;
	};

	class CIdType : public IType {
	public:
		CIdType( CIdExpression* theIdExpression );
		virtual ~CIdType() {}
		virtual std::string GetType() const override;
		virtual void Accept( IVisitor* v ) override;
		const std::shared_ptr<CIdExpression> GetIdExpression() const;
	private:
		std::shared_ptr<CIdExpression> idExpression;
	};


}
