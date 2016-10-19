#include "Argument.h"

FirstTask::CArgument::CArgument( std::shared_ptr<CType> theType,
	std::shared_ptr<CIdExpression> theIdExpression ) :
	type( theType ), idExpression( theIdExpression )
{
}

FirstTask::CArgument::~CArgument()
{
}