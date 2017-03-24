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
		Label( const int _name, const std::wstring& info = L"" );

		const int GetName() const;
		const std::wstring& GetInfo() const;
		std::wstring GetAssmeblerName();

	private:
		const std::wstring info;
		static int counter;
		int name;
	};
}
