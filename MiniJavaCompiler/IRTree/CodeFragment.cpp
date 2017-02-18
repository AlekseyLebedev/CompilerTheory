#include <memory>
#include "CodeFragment.h"

using namespace IRTree;

CCodeFragment::CCodeFragment( const std::shared_ptr<IRTStatement> body ) : body( body ), frame( 0 ), next( 0 )
{
	
}

void IRTree::CCodeFragment::SetNext( const std::shared_ptr<CCodeFragment> next )
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
