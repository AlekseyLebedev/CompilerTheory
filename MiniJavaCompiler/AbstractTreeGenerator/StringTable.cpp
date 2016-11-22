#include "StringTable.h"

namespace AbstractTreeGenerator {
	int CStringTable::insert( const std::string& theString )
	{
		auto iter = stringTable.find( theString );
		// ���� ������ ��� �����������, �� ���������� �� �����
		if( iter != stringTable.end() ) {
			return iter->second;
		}
		// ���� ���, �� ����������� ����� �����
		// ��������� ������������ �����
		int n = stringTable.size();
		// ����� ������ ������������� ������� �����
		stringTable.insert( std::make_pair( theString, n ) );
		return n;
	}

	//int CStringTable::find( const std::string& theString )
	//{
	//	auto iter = stringTable.find( theString );
	//	if( iter != stringTable.end() ) {
	//		return iter->second;
	//	}
	//	// � ������ ���� �� �����
	//	return 0;
	//}

	bool CStringTable::equals( const std::string& left, const std::string& right )
	{
		int leftNum = insert( left );
		int rightNum = insert( right );
		// TODO: ���� �� ������� ��� ��������� ��, ��� ��� ������ ������ ���� � �������
		// �.�. ��� find ������ �� ����
		return (leftNum == rightNum);
	}

}