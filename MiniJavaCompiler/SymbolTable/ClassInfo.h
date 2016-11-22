// ������ ���: ����� TypeCheker-�� ������� �����-������ �����
// ������������� ��� ������ � ���� � ��� � ���� � ���� � ��� � ��� ��� ���������
// ����� ����� ��������� ���������� � ������ ��� ������ �� TypeCheker-�
#pragma once
#include <vector>
#include "MethodInfo.h"
#include "VariableInfo.h"

namespace SymbolTable {

	// TODO: ������ ����� ������ ���� ������ �� ������ ����������� � ��������

	// ���������� � ������
	class CClassInfo {
	public:
		// �������� ���������� � ������ ������
		void insertMethod( const CMethodInfo theMethodInfo );
		// �������� ���������� � ���� ������ 
		void insertVariableInfo( const CVariableInfo theVariableInfo );
	private:
		// ���������� � �������
		std::vector<CMethodInfo> methods; // �������� ����� ������� ��������� �� MethodDeclaration �� ��
		// ���������� � �����
		std::vector<CVariableInfo> variables; // �������� ����� ������� ��������� �� VarDeclaration �� ��
	};
}