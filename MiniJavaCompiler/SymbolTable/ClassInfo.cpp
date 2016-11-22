#include "ClassInfo.h"

namespace SymbolTable {
	void CClassInfo::insertMethod( const CMethodInfo theMethodInfo )
	{
		methods.push_back( theMethodInfo );
	}

	void CClassInfo::insertVariableInfo( const CVariableInfo theVariableInfo )
	{
		variables.push_back( theVariableInfo );
	}
}