#include "MethodInfo.h"

namespace SymbolTable {

	int CMethodInfo::GetReturnType() const
	{
		return returnType;
	}

	void CMethodInfo::SetReturnType( const int id )
	{
		returnType = id;
	}

	const CVariableInfo & CMethodInfo::GetVarInfo( const int id ) const
	{
		auto info = vars.find( id );
		if( info == vars.end() )
			throw new std::logic_error( "Variable not found" );
		else
			return info->second;
	}

	void CMethodInfo::AddVariableInfo( const int id, const CVariableInfo & info )
	{
		vars[id] = info;
	}

	const std::vector<int>& CMethodInfo::GetArguments() const
	{
		return argments;
	}

	void CMethodInfo::SetArguments( const std::vector<int>& args )
	{
		argments = args;
	}
}