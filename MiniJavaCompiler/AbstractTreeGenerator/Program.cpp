#include "Program.h"

AbstractTreeGenerator::CProgram::CProgram( CMainClass* theMainClass,
	CClassDeclarationList* theClassDeclarationList ) :
	mainClass( theMainClass ), classDeclarationList( theClassDeclarationList )
{

}

AbstractTreeGenerator::CProgram::~CProgram()
{

}

void AbstractTreeGenerator::CProgram::Accept( IVisitor * v )
{
	v->visit( this );
}
const std::shared_ptr<AbstractTreeGenerator::CMainClass> AbstractTreeGenerator::CProgram::GetMainClass() const
{
	return mainClass;
}

const std::shared_ptr<AbstractTreeGenerator::CClassDeclarationList> AbstractTreeGenerator::CProgram::GetClassDeclarationList() const
{
	return classDeclarationList;
}

