// ������� ����� ��� ������� ��������
// ������ ������ ����� ��������������� ����������� �����
// � ��� ��������� ����� ����� ������ ������������ �� ������
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace AbstractTreeGenerator {

	class CStringTable {
	public:
		// ���������� ����� ����������� ����� ������, 0 - � ������ �������
		int insert( const std::string& theString );
		//// ���������� ����� ����������� ����� ������, 0 - � ������ ���������� ������
		//int find( const std::string& theString );

		// �������� ��������� �� ��� ������
		bool equals( const std::string& left, const std::string& right );

		// GetString( �� ������ );
	private:
		// ��� ��������� ����� ������������ ��������� �� ��������������� ������
		// ��� ������ Symbol ��������, ��� ��� ������ ��������� ������ ���� ���� � ������ ���� ������ Symbol.
		// �� ������ ������ ���������� �����
		std::unordered_map< std::string, int > stringTable;
	};

}