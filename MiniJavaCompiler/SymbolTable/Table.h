// ��� ���� ����� ��� ������ ������� �� ��� ����������� 
// ������ ����� ��������� TypeChecker-�� � ��������� ������ ������
// ��� ����� ��� ������� ������ �� ������:
//     ������ ��� ������� � ����������� � ��� - ��� �� ������ � ���������
//	       ���������� ���������� � ������������ ����, ���� ���������� � �������
//     ������ ����� ������ � ����������� � ���
#pragma once

#include <string>
#include <map>
#include <utility>
#include "Symbol.h"
#include "ClassInfo.h"
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\StringTable.h"

namespace SymbolTable {

	// ������� ��������
	class CTable {
	public:
		// �������� ����� ����� � ������� ��������
		void AddClass( const CSymbol& theSymbol, const CClassInfo& theClassInfo );
		const CClassInfo GetClassInfo( const CSymbol& theSymbol ) const;
		CClassInfo GetClassInfo( const int& id );
		int GetClass( const int& id );
	private:
		// ����������� �� ����� � ������
		AbstractTreeGenerator::CStringTable stringTable;

		// ����������� �� ������� � ���������� � ���
		std::vector<CSymbol> classes;
		std::vector<CClassInfo> classesInfo;
	
	};
}