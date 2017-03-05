#include <cassert>
#include "ClassInfo.h"
#include "TypeException.h"
#include "Table.h"
#include "..\AbstractTreeGenerator\Type.h"

namespace SymbolTable {
	CClassInfo::CClassInfo() : extend( CClassInfo::NothingExtend )
	{

	}
	CClassInfo::CClassInfo( int name_ ) : name( name_ ), extend( CClassInfo::NothingExtend )
	{
	}
	void CClassInfo::InsertMethod( int id, const CMethodInfo& theMethodInfo )
	{
		allMethods.push_back( theMethodInfo );
		methods[id] = theMethodInfo;
	}

	void CClassInfo::InsertVariableInfo( int id, const CVariableInfo& theVariableInfo )
	{
		allVariables.push_back( id );
		variables[id] = theVariableInfo;
	}

	const CVariableInfo & CClassInfo::GetVarInfo( const int id, const AbstractTreeGenerator::INode * brokenNode ) const
	{
		auto info = variables.find( id );
		if( info == variables.end() ) {
			assert( brokenNode != nullptr );
			throw new CTypeException( brokenNode->GetCol(), brokenNode->GetRow(), "Field not declarated" );
		} else {
			return info->second;
		}
	}

	const CMethodInfo & CClassInfo::GetMethodInfo( const int id, const AbstractTreeGenerator::INode * brokenNode ) const
	{
		auto info = methods.find( id );
		if( info == methods.end() ) {
			assert( brokenNode != nullptr );
			throw new CTypeException( brokenNode->GetCol(), brokenNode->GetRow(), "Method not declarated" );
		} else {
			return info->second;
		}
	}

	bool CClassInfo::ContainsMethod( const int id ) const
	{
		auto info = methods.find( id );
		return (info != methods.end());
	}

	bool CClassInfo::ContainsField( const int id ) const
	{
		auto info = variables.find( id );
		return (info != variables.end());
	}

	const std::vector<CMethodInfo>& CClassInfo::GetMethods() const
	{
		return allMethods;
	}
	const std::vector<int>& CClassInfo::GetVariables() const
	{
		return allVariables;
	}
	int CClassInfo::GetExtend() const
	{
		return extend;
	}
	void CClassInfo::SetExtend( const int id )
	{
		extend = id;
	}

	int CClassInfo::GetSize( const CTable* table ) const
	{
		int size = 0;
		if( extend != NothingExtend ) {
			size = table->GetClassInfo( extend ).GetSize( table );
		}
		for( size_t i = 0; i < allVariables.size(); i++ ) {
			size = addVairableToSize( i, size, table );
		}
		if( size == 0 ) {
			size = 1; // Иначе будут проблемы с массивами
		}
		if( size >= MachineWordSize ) {
			size = offset( size );
		}
		return size;
	}

	int CClassInfo::GetOffsetForField( const int id, const CTable* table ) const
	{
		auto info = variables.find( id );
		if( info == variables.end() ) {
			assert( extend != NothingExtend );
			return table->GetClassInfo( extend ).GetOffsetForField( id, table );
		} else {
			int position = 0;
			if( extend != NothingExtend ) {
				position = table->GetClassInfo( extend ).GetSize( table );
			}
			for( size_t i = 0; i < allVariables.size(); i++ ) {
				position = addVairableToSize( i, position, table );
				if( allVariables[i] == id ) {
					position -= GetSizeOfType( variables.find( id )->second.GetType(), table );
					return position;
				}
			}
		}
		return 0;
	}

	int CClassInfo::GetUniqueMethodsCount()
	{
		return methods.size();
	}

	const int CClassInfo::MachineWordSize = 4;

	int CClassInfo::offset( const int size )
	{
		return ((size + MachineWordSize - 1) / MachineWordSize) * MachineWordSize;
	}

	int CClassInfo::GetSizeOfType( const int type, const CTable* table )
	{
		switch( type ) {
			case AbstractTreeGenerator::TStandardType::ST_Bool:
				return 1;
			case AbstractTreeGenerator::TStandardType::ST_Int:
				return 4;
			case AbstractTreeGenerator::TStandardType::ST_Intlist:
				return MachineWordSize;
			case AbstractTreeGenerator::TStandardType::ST_StringList:
				return MachineWordSize; // Не используется!
			case AbstractTreeGenerator::TStandardType::ST_Void:
				assert( false );
				return -1;
			default:
				//return table->GetClassInfo( type ).GetSize( table );
				return MachineWordSize; //указатель
		}
	}

	int CClassInfo::addVairableToSize( int index, int size, const CTable* table ) const
	{
		int type = variables.find( allVariables[index] )->second.GetType();
		int fieldSize = GetSizeOfType( type, table );
		if( fieldSize >= MachineWordSize ) {
			size = offset( size );
		}
		size += fieldSize;
		return size;
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