#include "stdafx.h"
#include "LastExpList.h"

FirstTask::CLastExpList::CLastExpList(std::shared_ptr<FirstTask::
	IExpression> _exp) : exp(_exp) {

}

FirstTask::CLastExpList::~CLastExpList()
{
}

std::shared_ptr<FirstTask::IExpression> FirstTask::CLastExpList::
	GetExpression() const {
	return exp;
}

void FirstTask::CLastExpList::Accept(FirstTask::IVisitor* v) {
	v->Visit(this);
}
