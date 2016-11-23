#include "Table.h"

namespace SymbolTable {
	void SymbolTable::CTable::AddClassInfo( const int id, const CClassInfo & info )
	{
		classesInfos[id] = info;
		++additionCount;
	}

	CTable::CTable() : additionCount( 0 )
	{
	}

	const CClassInfo & CTable::GetClassInfo( const int & id ) const
	{
		auto info = classesInfos.find( id );
		if( info == classesInfos.end() )
			throw std::logic_error( "Class not found" );
		else
			return info->second;
	}
	int CTable::TotalAdditionCount() const
	{
		return additionCount;
	}
	int CTable::UniqueClassesCount() const
	{
		return classesInfos.size();
	}
}