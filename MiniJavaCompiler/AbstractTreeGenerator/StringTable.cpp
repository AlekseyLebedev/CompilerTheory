#include "StringTable.h"

namespace AbstractTreeGenerator {

	CStringTable::CStringTable()
	{
		stringTable.insert( std::make_pair( "", 0 ) );
	}

	int CStringTable::insert( const std::string& theString )
	{
		auto iter = stringTable.find( theString );
		if( iter != stringTable.end() ) {
			// �����  �������, ��� 0 - ������� ������
			return 0;
		}
		// ��������� ������������ �����
		int n = stringTable.size();
		// ����� ������ ������������� ������� �����
		stringTable.insert( std::make_pair( theString, n ) );
		return n;
	}

	int CStringTable::find( const std::string& theString )
	{
		auto iter = stringTable.find( theString );
		if( iter != stringTable.end() ) {
			return iter->second;
		}
		// � ������ ���� �� �����
		return 0;
	}

	bool CStringTable::equals( const std::string& left, const std::string& right )
	{
		int leftNum = find( left );
		int rightNum = find( right );
		// TODO: ���� �� ������� ��� ��������� ��, ��� ��� ������ ������ ���� � �������
		// �.�. ��� find ������ �� ����
		return (leftNum == rightNum);
	}

}