// ������� ����� ��� ������� ��������
// ������ ������ ����� ��������������� ����������� �����
// � ��� ��������� ����� ����� ������ ������������ �� ������
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "StringTable.h"

namespace AbstractTreeGenerator {

	class CStringTable {
	public:
		// ���������� ����� ����������� ����� ������
		int insert( const std::string& theString );
		// ���������� ������ �� ������ 
		std::string find( const int num );
		std::wstring wfind( const int num );

		// �������� ��������� �� ��� ������
		bool equals( const std::string& left, const std::string& right );

	private:
		// ��� ��������� ����� ����� ������������ ���������� �����
		// ��� ������ Symbol ��������, ��� ��� ������ ��������� ������ ���� ���� � ������ ���� ������ Symbol.
		// �� ������ ������ ���������� �����
		// � ����� ������� ������ ��� ������, ���� ��� ����������� ���� ������ � �� �� �����
		std::unordered_map< std::string, int > stringTable;
		std::vector<std::string> v;
	};

}