#include "NumExpression.h"

FirstTask::CNumExpression::CNumExpression( int theValue ) : value( theValue )
{
}

FirstTask::CNumExpression::~CNumExpression()
{
}

void FirstTask::CNumExpression::Accept( IVisitor* v )
{
	v->Visit( this );
}