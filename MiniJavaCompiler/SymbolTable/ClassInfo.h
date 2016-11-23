// ������ ���: ����� TypeCheker-�� ������� �����-������ �����
// ������������� ��� ������ � ���� � ��� � ���� � ���� � ��� � ��� ��� ���������
// ����� ����� ��������� ���������� � ������ ��� ������ �� TypeCheker-�
#pragma once
#include <vector>
#include <map>
#include "MethodInfo.h"
#include "VariableInfo.h"

namespace SymbolTable {
	// ���������� � ������
	class CClassInfo {
	public:
		CClassInfo();

		// �������� ���������� � ������ ������
		void InsertMethod( int id, const CMethodInfo & theMethodInfo );
		// �������� ���������� � ���� ������ 
		void InsertVariableInfo( int id, const CVariableInfo & theVariableInfo );

		const CVariableInfo& GetVarInfo( const int id )const;
		const CMethodInfo& GetMethodInfo( const int id ) const;
		const std::vector<CMethodInfo>& GetMethods() const;

		int GetExtend();
		void SetExtend(const int id);


		int GetUniqueMethodsCount();


		static const int NothingExtend;
	private:
		// ���������� � �������
		std::vector<CMethodInfo> allMethods;
		std::map<int, CMethodInfo> methods;
		// ���������� � �����
		std::map<int, CVariableInfo> variables; // �������� ����� ������� ��������� �� VarDeclaration �� ��

		int extend;
	};
}