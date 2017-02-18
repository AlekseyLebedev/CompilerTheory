#pragma once

#include <string>

//TO DO
namespace IRTree {

	// ����������������� ��� ����������� ������� ������
	enum TStandadLabel { 
		SL_NotUsed = 0, // ����������������� ��������, ������ ������������
		SL_Alloc = 1,
		SL_PrintLn = 2,
		SL_Count // ������ ���� � �����!!!!! (������������ ��� ������������ ��������� �������  Label::counter)
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
