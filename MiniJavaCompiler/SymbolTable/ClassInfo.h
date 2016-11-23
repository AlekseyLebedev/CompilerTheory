// идейно так: когда TypeCheker-ом обходим какой-нибудь класс
// просматриваем его методы и инфу о них и поля и инфу о них и так все проверяем
// нужно уметь заполнять информацию о классе при обходе до TypeCheker-а
#pragma once
#include <vector>
#include <map>
#include "MethodInfo.h"
#include "VariableInfo.h"

namespace SymbolTable {
	// информация о классе
	class CClassInfo {
	public:
		CClassInfo();

		// добавить информацию о методе класса
		void InsertMethod( int id, const CMethodInfo & theMethodInfo );
		// добавить информацию о поле класса 
		void InsertVariableInfo( int id, const CVariableInfo & theVariableInfo );

		const CVariableInfo& GetVarInfo( const int id )const;
		const CMethodInfo& GetMethodInfo( const int id ) const;
		const std::vector<CMethodInfo>& GetMethods() const;

		int GetExtend();
		void SetExtend(const int id);


		int GetUniqueMethodsCount();


		static const int NothingExtend;
	private:
		// информация о методах
		std::vector<CMethodInfo> allMethods;
		std::map<int, CMethodInfo> methods;
		// инфомрация о полях
		std::map<int, CVariableInfo> variables; // возможно здесь следует ссылаться на VarDeclaration но хз

		int extend;
	};
}