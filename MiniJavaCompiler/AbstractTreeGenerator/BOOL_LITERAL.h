// TODO: ��� �����, ����� ���� ������� ������� � �������� value string � �� bool, 
// �� bool ���� �� ��������

#pragma once
#include <string>

namespace AbstractTreeGenerator {
	class CBOOL_LITERAL{
	public:
		CBOOL_LITERAL(std::string theValue);
		CBOOL_LITERAL(bool theValue);
		virtual ~CBOOL_LITERAL();
	private:
		bool value;
	};
}