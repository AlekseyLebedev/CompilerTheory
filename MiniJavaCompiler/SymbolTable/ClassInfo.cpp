#include "ClassInfo.h"

namespace SymbolTable {
	void CClassInfo::InsertMethod( const CMethodInfo theMethodInfo )
	{
		methods.push_back( theMethodInfo );
	}

	void CClassInfo::InsertVariableInfo( const CVariableInfo theVariableInfo )
	{
		variables.push_back( theVariableInfo );
	}
}