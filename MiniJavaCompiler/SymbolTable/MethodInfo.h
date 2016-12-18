#pragma once
#include "VariableInfo.h"
#include <vector>
#include <map>
#include "..\AbstractTreeGenerator\INode.h"


namespace SymbolTable {

	// TODO: Каждый метод должен быть привязан к своим параметрам, локальным переменным и возвращаемому значению

	// информация о методах
	class CMethodInfo {
	public:
		int GetReturnType() const;
		void SetReturnType( const int id );
		const CVariableInfo & GetVarInfo( const int id, const AbstractTreeGenerator::INode * brokenNode ) const;
		void AddVariableInfo( const int id, const CVariableInfo& info );
		const CVariableInfo & GetArgInfo( const int id, const AbstractTreeGenerator::INode * brokenNode ) const;
		void AddArgInfo( const int id, const CVariableInfo& info );
		int GetUniqueArgsCount();
		int GetUniqueVarsCount();
		int GetAllArgsCount();
		int GetAllVarsCount();
		int GetArgType( const int num ) const;

	private:
		int returnType;
		std::map<int, CVariableInfo> vars;
		std::map<int, CVariableInfo> args;
		int varsCount;
		std::vector<int> argsTypes;
	};
}