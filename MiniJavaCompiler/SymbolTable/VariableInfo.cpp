#include "VariableInfo.h"

namespace SymbolTable {
	int CVariableInfo::GetType() const
	{
		return type;
	}
	CVariableInfo::CVariableInfo()
	{
	}
	CVariableInfo::CVariableInfo( int _type ) :
		type( _type )
	{
	}
}