// ������ ���: ����� TypeCheker-�� ������� �����-������ �����
// ������������� ��� ������ � ���� � ��� � ���� � ���� � ��� � ��� ��� ���������
// ����� ����� ��������� ���������� � ������ ��� ������ �� TypeCheker-�
#pragma once
#include <vector>
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
		void insertMethod( const CMethodInfo theMethodInfo );
		// �������� ���������� � ���� ������ 
		void insertVariableInfo( const CVariableInfo theVariableInfo );

		CVariableInfo GetVarInfo( const int& id );
		std::vector<CMethodInfo> GetMethods();
	private:
		// ���������� � �������
		std::vector<CMethodInfo> methods; // �������� ����� ������� ��������� �� MethodDeclaration �� ��
		// ���������� � �����
		std::vector<CVariableInfo> variables; // �������� ����� ������� ��������� �� VarDeclaration �� ��
	};
}