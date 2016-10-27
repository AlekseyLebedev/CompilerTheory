#include "LastExpressionList.h"
#include <memory>

AbstractTreeGenerator::CLastExpressionList::CLastExpressionList(AbstractTreeGenerator::
	IExpression* _exp) : exp(_exp) {

}

AbstractTreeGenerator::CLastExpressionList::~CLastExpressionList()
{
}

std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CLastExpressionList::
	GetExpression() const {
	return exp;
}

void AbstractTreeGenerator::CLastExpressionList::Accept(AbstractTreeGenerator::IVisitor* v) {
	v->visit(this);
}
const std::shared_ptr<AbstractTreeGenerator::IExpression> AbstractTreeGenerator::CLastExpressionList::GetExp() const
{
	 return exp;
}

