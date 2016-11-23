// ������ ���: ����� TypeCheker-�� ������� �����-������ �����
// ������������� ��� ������ � ���� � ��� � ���� � ���� � ��� � ��� ��� ���������
// ����� ����� ��������� ���������� � ������ ��� ������ �� TypeCheker-�
#pragma once
#include <vector>
#include <map>
#include "MethodInfo.h"
#include "VariableInfo.h"

namespace SymbolTable {

	// TODO: ������ ����� ������ ���� ������ �� ������ ����������� � ��������
	// TODO: �������� ������ ��� ������ ���������� - TypeCheker ����� �������� ��� ������
	// � ��������� ������� ��� ����� ������� ���������� methods � variables

	// ���������� � ������
	class CClassInfo {
	public:
		// �������� ���������� � ������ ������
		void InsertMethod( const CMethodInfo theMethodInfo );
		// �������� ���������� � ���� ������ 
		void InsertVariableInfo( const CVariableInfo theVariableInfo );

		CVariableInfo GetVarInfo( const int& id );
		std::vector<CMethodInfo> GetMethods();

		int GetExtend();

		const int NothingExtend;
	private:
		// ���������� � �������
		std::vector<CMethodInfo> methods; // �������� ����� ������� ��������� �� MethodDeclaration �� ��
		// ���������� � �����
		std::map<int, CVariableInfo> variables; // �������� ����� ������� ��������� �� VarDeclaration �� ��
	};
}