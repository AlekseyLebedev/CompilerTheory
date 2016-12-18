#pragma once

#include <string>
#include <map>
#include <utility>
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"
#include "TypeException.h"

namespace SymbolTable {

	class CTable {
	public:
		CTable();
		const CClassInfo& GetClassInfo( const int& id , const AbstractTreeGenerator::INode * brokenNode ) const;
		void AddClassInfo(const int id, const CClassInfo& info );
		int TotalAdditionCount() const ;
		int UniqueClassesCount() const ;		
	private:
		int additionCount;
		std::map<int, CClassInfo> classesInfos;
	};
}