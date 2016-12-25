// идейно так: когда TypeCheker-ом обходим какой-нибудь класс
// просматриваем его методы и инфу о них и поля и инфу о них и так все проверяем
// нужно уметь заполнять информацию о классе при обходе до TypeCheker-а
#pragma once
#include <vector>
#include <map>
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\INode.h"
#include "TypeException.h"

namespace SymbolTable {
	class CTable;

	// информация о классе
	class CClassInfo {
	public:
		CClassInfo();
		CClassInfo( int name_ );
		// добавить информацию о методе класса
		void InsertMethod( int id, const CMethodInfo & theMethodInfo );
		// добавить информацию о поле класса 
		void InsertVariableInfo( int id, const CVariableInfo & theVariableInfo );

		const CVariableInfo& GetVarInfo( const int id, const AbstractTreeGenerator::INode * brokenNode = 0 )const;
		const CMethodInfo& GetMethodInfo( const int id, const AbstractTreeGenerator::INode * brokenNode = 0 ) const;
		const std::vector<CMethodInfo>& GetMethods() const;

		int GetExtend() const;
		void SetExtend( const int id );

		// Размеры в байтах
		int GetSize( const CTable* ) const;
		int GetOffsetForField( const int id, const CTable* ) const;

		int GetUniqueMethodsCount();
		friend bool operator ==( CClassInfo a, CClassInfo b );
		friend bool operator !=( CClassInfo a, CClassInfo b );
		static const int NothingExtend;
	private:
		int name;
		// информация о методах
		std::vector<CMethodInfo> allMethods;
		std::map<int, CMethodInfo> methods;
		// инфомрация о полях
		std::map<int, CVariableInfo> variables; // возможно здесь следует ссылаться на VarDeclaration но хз
		std::vector<int> allVariables; // Храним порядок в названиях
		int extend;

		static const int machineWordSize;
		static int offset( const int size );
		static int getSizeOfType( const int type, const CTable * table );
		int addVairableToSize( int index, int size, const CTable * table ) const;
	};
}