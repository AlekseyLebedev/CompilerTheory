#include "MainClass.h"

AbstractTreeGenerator::CMainClass::CMainClass( std::shared_ptr<CIdExpression> theClassName,
	std::shared_ptr<CIdExpression> theArgv,
	std::shared_ptr<IStatement> theStatement ) : className( theClassName ), argv( theArgv ), statement( theStatement )
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
