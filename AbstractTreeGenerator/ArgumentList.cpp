#include "ArgumentList.h"

FirstTask::CArgumentList::CArgumentList( std::shared_ptr<CArgument> theArgument,
	std::shared_ptr<CArgumentList> theArgumentList ) :
	argument( theArgument ), argumentList( theArgumentList )
{
}

FirstTask::CArgumentList::~CArgumentList()
{
}