#include <string>
#include <memory>
#include "AssignStatement.h"

FirstTask::CAssignStatement::CAssignStatement(const std::string name, std::shared_ptr<IExpression> operation) : 
	variableName(name), expression(operation)
{	
}

FirstTask::CAssignStatement::~CAssignStatement()
{
}

std::string FirstTask::CAssignStatement::GetVariableName() const {
	return variableName;
}

std::shared_ptr<FirstTask::IExpression> FirstTask::CAssignStatement::GetExpression() const
{
	return expression;
}

void FirstTask::CAssignStatement::Accept(IVisitor* v) {
	v->Visit(this);
}