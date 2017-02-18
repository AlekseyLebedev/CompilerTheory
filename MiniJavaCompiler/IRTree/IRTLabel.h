#pragma once

#include <string>

//TO DO
namespace IRTree {

	// Зарезерверованные под стандартные функции лэйблы
	enum TStandadLabel { 
		SL_NotUsed = 0, // Зарезервираванное значение, нельзя использовать
		SL_Alloc = 1,
		SL_PrintLn = 2,
		SL_Count // Должно идти в конце!!!!! (используется для инициализаии итератора лэйблов  Label::counter)
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
