#include "MainClass.h"

FirstTask::CMainClass::CMainClass(std::shared_ptr<CIdExpression> theClassName,
	std::shared_ptr<CIdExpression> theArgv,
	std::shared_ptr<IStatemnet> theCode) : className(theClassName), argv(theArgv), code(theCode)
{

}

FirstTask::CMainClass::~CMainClass() {

}

std::shared_ptr<FirstTask::CIdExpression> FirstTask::CMainClass::GetName() const{
	return className;
}
