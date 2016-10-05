#include "LastExpressionList.h"
#include <memory>

FirstTask::CLastExpressionList::CLastExpressionList(std::shared_ptr<FirstTask::
	IExpression> _exp) : exp(_exp) {

}

FirstTask::CLastExpressionList::~CLastExpressionList()
{
}

std::shared_ptr<FirstTask::IExpression> FirstTask::CLastExpressionList::
	GetExpression() const {
	return exp;
}

void FirstTask::CLastExpressionList::Accept(FirstTask::IVisitor* v) {
	v->Visit(this);
}
