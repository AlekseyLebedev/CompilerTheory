#pragma once

#include "stdafx.h"
#include "IExpression.h"

namespace FirstTask {
	class CLastExpList : public IExpression {
	public:
		CLastExpList(std::shared_ptr<IExpression> _exp);
		virtual ~CLastExpList();
		virtual void Accept(IVisitor* v) override;
		std::shared_ptr<IExpression> GetExpression() const; 
	private:
		std::shared_ptr<IExpression> exp;
	};
}
