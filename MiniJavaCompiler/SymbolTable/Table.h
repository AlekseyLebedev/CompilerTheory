﻿#pragma once

#include <string>
#include <map>
#include <utility>
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"
#include "TypeException.h"
#include "..\IRTree\IRTLabel.h"

namespace SymbolTable {

	class CTable {
	public:
		CTable();
		const CClassInfo& GetClassInfo( const int& id , const AbstractTreeGenerator::INode * brokenNode = 0 ) const;
		void AddClassInfo(const int id, const CClassInfo& info );
		int TotalAdditionCount() const ;
		int UniqueClassesCount() const ;

		std::shared_ptr<IRTree::Label> GetAllocLabel() const;
		std::shared_ptr<IRTree::Label> GetPrintLnLabel() const;


	private:
		int additionCount;
		std::map<int, CClassInfo> classesInfos;

		mutable std::shared_ptr<IRTree::Label> allocLabel;
		mutable std::shared_ptr<IRTree::Label> printLnLabel;
	};
}