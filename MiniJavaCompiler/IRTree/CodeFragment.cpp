#include "CodeFragment.h"

using namespace IRTree;

CCodeFragment::CCodeFragment( const IRTStatement* body ) : body( body ), frame( 0 ), next( 0 )
{
	
}

void IRTree::CCodeFragment::SetNext( const CCodeFragment * next )
{
	this->next = next;
}

const IRTStatement* CCodeFragment::GetTree() const
{
	return body;
}

const CCodeFragment* CCodeFragment::GetNext() const
{
	return next;
}
