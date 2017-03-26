#pragma once

#include <string>

namespace CodeGeneration {

	enum TOperationType {
		OT_None, // Не используется!
		OT_Move, // Должно использоваться отдельно, для распределенияр регистров
		OT_MemFramePointerPlusConst, // Обращеине к ISP + константа
		OT_MemRegPlusConst, // Обращеине регистр + константа
		OT_MemRegMinusConst, // Обращеине регистр - константа
		OT_MemConstMinusReg, // Обращеине константа - регистр
		OT_MemRegMulConst, // Обращеине регистр * константа
		OT_AddConstToFirst, // Добавление к первому аргументу и т.д.
		OT_AddTemps, // Бинарная операция сложения регистров
		OT_SubTemps, // Бинарная операция вычитания регистров
		OT_MulTemps, // Бинарная операция умножения регистров
		OT_DivTemps, // Бинарная операция деления регистров
		OT_AddTempConst, // Бинарная операция сложения регистра с константой
		OT_SubTempConst, // Бинарная операция вычитания регистра с константой
		OT_MulTempConst, // Бинарная операция умножения регистра с константой
		OT_DivTempConst, // Бинарная операция деления регистра с константой
		OT_LoadConst, // Запоминаем константу в регистр
		OT_JMP, // безусловный прыжок
		OT_JE,  // нуль или равно // ZF=1
		OT_JNE // не нуль или не равно // ZF = 0
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion