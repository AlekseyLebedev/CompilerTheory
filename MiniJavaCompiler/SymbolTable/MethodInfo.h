#pragma once
#include "VariableInfo.h"
#include <vector>
#include <map>
#include "..\AbstractTreeGenerator\INode.h"
#include "..\IRTree\IRTLabel.h"

namespace SymbolTable {

	// TODO: Каждый метод должен быть привязан к своим параметрам, локальным переменным и возвращаемому значению

	// информация о методах
	class CMethodInfo {
	public:
		int GetReturnType() const;
		void SetReturnType( const int id );
		const CVariableInfo & GetVarInfo( const int id, const AbstractTreeGenerator::INode * brokenNode = 0 ) const;
		void AddVariableInfo( const int id, const CVariableInfo& info );
		const CVariableInfo & GetArgInfo( const int id, const AbstractTreeGenerator::INode * brokenNode = 0 ) const;
		void AddArgInfo( const int id, const CVariableInfo& info );
		int GetUniqueArgsCount() const;
		int GetUniqueVarsCount() const;
		int GetAllArgsCount() const;
		int GetAllVarsCount() const;
		int GetArgType( const int num ) const;
		IRTree::Label* GetLabel() const;

	private:
		int returnType;
		std::map<int, CVariableInfo> vars;
		std::map<int, CVariableInfo> args;
		int varsCount;
		std::vector<int> argsTypes;
		mutable IRTree::Label* label;
		static int methodCount;
	};
}