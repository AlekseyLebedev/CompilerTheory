#include "MainClass.h"

AbstractTreeGenerator::CMainClass::CMainClass( CIdExpression* theClassName,
	CIdExpression* theArgv,
	IStatement* theStatement ) : className( theClassName ), argv( theArgv ), statement( theStatement )
{

}

AbstractTreeGenerator::CMainClass::~CMainClass()
{

}

void AbstractTreeGenerator::CMainClass::Accept( IVisitor * v)
{
	v->visit( this );
}

std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CMainClass::GetName() const
{
	return className;
}
const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CMainClass::GetClassName() const
{
	 return className;
}

const std::shared_ptr<AbstractTreeGenerator::CIdExpression> AbstractTreeGenerator::CMainClass::GetArgv() const
{
	 return argv;
}

const std::shared_ptr<AbstractTreeGenerator::IStatement> AbstractTreeGenerator::CMainClass::GetStatement() const
{
	 return statement;
}

