#include "ClassInfo.h"

namespace SymbolTable {
	CClassInfo::CClassInfo() : extend( CClassInfo::NothingExtend )
	{

	}
	void CClassInfo::InsertMethod( int id, const CMethodInfo& theMethodInfo )
	{
		allMethods.push_back( theMethodInfo );
		methods[id] = theMethodInfo;
	}

	void CClassInfo::InsertVariableInfo( int id, const CVariableInfo& theVariableInfo )
	{
		variables[id] = theVariableInfo;
	}

	const CVariableInfo & CClassInfo::GetVarInfo( const int id ) const
	{
		auto info = variables.find( id );
		if( info == variables.end() )
			throw std::logic_error( "Variable not found" );
		else
			return info->second;
	}

	const CMethodInfo & CClassInfo::GetMethodInfo( const int id ) const
	{
		auto info = methods.find( id );
		if( info == methods.end() )
			throw std::logic_error( "Method not found" );
		else
			return info->second;
	}

	const std::vector<CMethodInfo>& CClassInfo::GetMethods() const
	{
		return allMethods;
	}
	int CClassInfo::GetExtend()
	{
		return extend;
	}
	void CClassInfo::SetExtend( const int id )
	{
		extend = id;
	}
	int CClassInfo::GetUniqueMethodsCount()
	{
		return methods.size();
	}

	const int CClassInfo::NothingExtend = -10;
}