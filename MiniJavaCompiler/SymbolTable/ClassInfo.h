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
	class CTable;

	// ���������� � ������
	class CClassInfo {
	public:
		CClassInfo();
		CClassInfo( int name_ );
		// �������� ���������� � ������ ������
		void InsertMethod( int id, const CMethodInfo & theMethodInfo );
		// �������� ���������� � ���� ������ 
		void InsertVariableInfo( int id, const CVariableInfo & theVariableInfo );

		const CVariableInfo& GetVarInfo( const int id, const AbstractTreeGenerator::INode * brokenNode = 0 )const;
		const CMethodInfo& GetMethodInfo( const int id, const AbstractTreeGenerator::INode * brokenNode = 0 ) const;
		const std::vector<CMethodInfo>& GetMethods() const;

		int GetExtend() const;
		void SetExtend( const int id );

		// ������� � ������
		int GetSize( const CTable* ) const;
		int GetOffsetForField( const int id, const CTable* ) const;

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
		std::vector<int> allVariables; // ������ ������� � ���������
		int extend;

		static const int machineWordSize;
		static int offset( const int size );
		static int getSizeOfType( const int type, const CTable * table );
		int addVairableToSize( int index, int size, const CTable * table ) const;
	};
}