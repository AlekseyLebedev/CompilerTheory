#include "Program.h"

AbstractTreeGenerator::CProgram::CProgram( std::shared_ptr<CMainClass> theMainClass,
	std::shared_ptr<CClassDeclarationList> theClassDeclarationList ) :
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
