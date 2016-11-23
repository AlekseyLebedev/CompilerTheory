// идейно так: когда TypeCheker-ом обходим какой-нибудь класс
// просматриваем его методы и инфу о них и поля и инфу о них и так все проверяем
// нужно уметь заполнять информацию о классе при обходе до TypeCheker-а
#pragma once
#include <vector>
#include "MethodInfo.h"
#include "VariableInfo.h"

namespace SymbolTable {

	// TODO: Каждый класс должен быть связан со своими переменными и методами
	// TODO: добавить методы для поиска инфомрации - TypeCheker может вызывать эти методы
	// и проверять правила или можно сделать публичными methods и variables

	// информация о классе
	class CClassInfo {
	public:
		// добавить информацию о методе класса
		void insertMethod( const CMethodInfo theMethodInfo );
		// добавить информацию о поле класса 
		void insertVariableInfo( const CVariableInfo theVariableInfo );

		CVariableInfo GetVarInfo( const int& id );
		std::vector<CMethodInfo> GetMethods();
	private:
		// информация о методах
		std::vector<CMethodInfo> methods; // возможно здесь следует ссылаться на MethodDeclaration но хз
		// инфомрация о полях
		std::vector<CVariableInfo> variables; // возможно здесь следует ссылаться на VarDeclaration но хз
	};
}