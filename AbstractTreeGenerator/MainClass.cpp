#include "MainClass.h"

FirstTask::CMainClass::CMainClass( std::shared_ptr<CIdExpression> theClassName,
	std::shared_ptr<CIdExpression> theArgv,
	std::shared_ptr<IStatement> theStatement ) : className( theClassName ), argv( theArgv ), statement( theStatement )
{

}

FirstTask::CMainClass::~CMainClass()
{

}

std::shared_ptr<FirstTask::CIdExpression> FirstTask::CMainClass::GetName() const
{
	return className;
}
