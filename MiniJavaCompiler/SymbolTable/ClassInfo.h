// ������ ���: ����� TypeCheker-�� ������� �����-������ �����
// ������������� ��� ������ � ���� � ��� � ���� � ���� � ��� � ��� ��� ���������
// ����� ����� ��������� ���������� � ������ ��� ������ �� TypeCheker-�
#pragma once
#include <vector>
#include <map>
#include "MethodInfo.h"
#include "VariableInfo.h"
#include "..\AbstractTreeGenerator\INode.h"
#include "TypeException.h"

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

		const CVariableInfo& GetVarInfo( const int id, const AbstractTreeGenerator::INode * brokenNode )const;
		const CMethodInfo& GetMethodInfo( const int id, const AbstractTreeGenerator::INode * brokenNode ) const;
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