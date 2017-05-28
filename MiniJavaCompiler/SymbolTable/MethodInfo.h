#pragma once
#include "VariableInfo.h"
#include <vector>
#include <map>
#include <memory>
#include "..\AbstractTreeGenerator\INode.h"
#include "..\IRTree\IRTLabel.h"

namespace SymbolTable {

	// TODO: Каждый метод должен быть привязан к своим параметрам, локальным переменным и возвращаемому значению

	// информация о методах
	class CMethodInfo {
	public:
		CMethodInfo();
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
		std::shared_ptr<IRTree::Label> GetLabel() const;
		void SetName( int id );

	private:
		int returnType;
		int name;
		std::map<int, CVariableInfo> vars;
		std::map<int, CVariableInfo> args;
		int varsCount;
		std::vector<int> argsTypes;
		mutable std::shared_ptr<IRTree::Label> label;
		static int methodCount;
	};
}