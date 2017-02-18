#pragma once

#include <string>

//TO DO
namespace IRTree {

	// ����������������� ��� ����������� ������� ������
	enum TStandadLabel { 
		TSL_NotUsed = 0, // ����������������� ��������, ������ ������������
		TSL_Alloc = 1,
		TSL_PrintLn = 2,
		TSL_Count // ������ ���� � �����!!!!! (������������ ��� ������������ ��������� �������  Label::counter)
	};

	class Label {
	public:

		Label();
		Label( const int _name );

		const int GetName() const;

	private:

		static int counter;
		int name;
	};
}
