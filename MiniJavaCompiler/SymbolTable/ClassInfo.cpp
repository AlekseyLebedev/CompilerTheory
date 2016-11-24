#include "ClassInfo.h"
#include "TypeException.h"

namespace SymbolTable {
	CClassInfo::CClassInfo() : extend( CClassInfo::NothingExtend )
	{

	}
	CClassInfo::CClassInfo( int name_ ) : name( name_ )
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

	const CVariableInfo & CClassInfo::GetVarInfo( const int id, const AbstractTreeGenerator::INode * brokenNode ) const
	{
		auto info = variables.find( id );
		if( info == variables.end() )
			throw new CTypeException( brokenNode->GetCol(), brokenNode->GetRow(), "Field not declarated" );
		else
			return info->second;
	}

	const CMethodInfo & CClassInfo::GetMethodInfo( const int id, const AbstractTreeGenerator::INode * brokenNode ) const
	{
		auto info = methods.find( id );
		if( info == methods.end() )
			throw new CTypeException( brokenNode->GetCol(), brokenNode->GetRow(), "Method not declarated" );
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
	bool operator==( CClassInfo a, CClassInfo b )
	{
		return a.name == b.name;
	}
	bool operator!=( CClassInfo a, CClassInfo b )
	{
		return a.name != b.name;
	}
}