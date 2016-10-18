#include "Program.h"

FirstTask::CProgram::CProgram( std::shared_ptr<CMainClass> theMainClass,
	std::shared_ptr<CClassDeclarationList> theClassDeclarationList ) :
	mainClass( theMainClass ), classDeclarationList( theClassDeclarationList )
{

}

FirstTask::CProgram::~CProgram()
{

}