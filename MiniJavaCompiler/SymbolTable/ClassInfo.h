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
		CClassInfo(int name_);
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
		friend bool operator ==( CClassInfo a, CClassInfo b );
		friend bool operator !=( CClassInfo a, CClassInfo b );
		static const int NothingExtend;
	private:
		int name;
		// ���������� � �������
		std::vector<CMethodInfo> allMethods;
		std::map<int, CMethodInfo> methods;
		// ���������� � �����
		std::map<int, CVariableInfo> variables; // �������� ����� ������� ��������� �� VarDeclaration �� ��

		int extend;
	};
}