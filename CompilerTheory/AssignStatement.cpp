#include "stdafx.h"
#include "AssignStatement.h"

FirstTask::CAssignStatement::CAssignStatement(const std::string name) :
	variableName(name)
{	
}

FirstTask::CAssignStatement::~CAssignStatement()
{
}

std::string FirstTask::CAssignStatement::GetVariableName() const {
	return variableName;
}

void FirstTask::CAssignStatement::Accept(IVisitor* v) {
	v->Visit(this);
}