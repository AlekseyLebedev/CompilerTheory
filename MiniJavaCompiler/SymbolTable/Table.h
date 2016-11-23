#pragma once

#include <string>
#include <map>
#include <utility>
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"

namespace SymbolTable {

	class CTable {
	public:
		const CClassInfo& GetClassInfo( const int& id );
		int GetClass( const int& id );
	private:
		AbstractTreeGenerator::CStringTable stringTable;
		std::map<int, CClassInfo> classesInfo;

	};
}