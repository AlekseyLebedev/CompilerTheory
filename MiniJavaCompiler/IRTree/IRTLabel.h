#pragma once

#include <string>

//TO DO
namespace IRTree {

	// Зарезерверованные под стандартные функции лэйблы
	enum TStandadLabel { 
		TSL_NotUsed = 0, // Зарезервираванное значение, нельзя использовать
		TSL_Alloc = 1,
		TSL_PrintLn = 2,
		TSL_Count // Должно идти в конце!!!!! (используется для инициализаии итератора лэйблов  Label::counter)
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
