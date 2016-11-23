#pragma once
#include "VariableInfo.h"
#include <vector>
#include <map>

namespace SymbolTable {

	// TODO: Каждый метод должен быть привязан к своим параметрам, локальным переменным и возвращаемому значению

	// информация о методах
	class CMethodInfo {
	public:
		int GetReturnType() const;
		void SetReturnType( const int id );
		const CVariableInfo& GetVarInfo( const int id ) const;
		void AddVariableInfo( const int id, const CVariableInfo& info );
		const std::vector<int>& GetArguments() const;
		void SetArguments( const std::vector<int>& args );
	private:
		int returnType;
		std::map<int, CVariableInfo> vars;
		std::vector<int> argments;
	};
}