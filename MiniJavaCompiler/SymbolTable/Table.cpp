#include <cassert>
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

	const CClassInfo & CTable::GetClassInfo( const int & id, const AbstractTreeGenerator::INode * brokenNode ) const
	{
		auto info = classesInfos.find( id );
		if( info == classesInfos.end() ) {
			assert( brokenNode != 0 );
			throw new CTypeException( brokenNode->GetCol(), brokenNode->GetRow(), "Class not declarated" );
		} else {
			return info->second;
		}
	}
	int CTable::TotalAdditionCount() const
	{
		return additionCount;
	}
	int CTable::UniqueClassesCount() const
	{
		return classesInfos.size();
	}

	std::shared_ptr<IRTree::Label> CTable::GetAllocLabel() const
	{
		if( allocLabel == 0 ) {
			allocLabel = std::make_shared<IRTree::Label>( IRTree::SL_Alloc );
		}
		return allocLabel;
	}

	std::shared_ptr<IRTree::Label> CTable::GetPrintLnLabel() const
	{
		if( printLnLabel == 0 ) {
			printLnLabel = std::make_shared<IRTree::Label>( IRTree::SL_PrintLn );
		}
		return printLnLabel;
	}
}