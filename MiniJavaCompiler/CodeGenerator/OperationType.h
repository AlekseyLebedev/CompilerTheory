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
		OT_MemConst, // Обращеине в память по константe
		OT_MemReg, // Обращеине в память по значению из регистра
		OT_Call, // Вызов функции
		OT_AddConstToFirst, // Добавление к первому аргументу и т.д.
		OT_AddTemps, // Бинарная операция сложения регистров
		OT_SubTemps, // Бинарная операция вычитания регистров
		OT_MulTemps, // Бинарная операция умножения регистров
		OT_DivTemps, // Бинарная операция деления регистров
		OT_AddTempConst, // Бинарная операция сложения регистра с константой
		OT_SubTempConstLeft, // Бинарная операция вычитания регистра с константой слева
		OT_SubTempConstRight, // Бинарная операция вычитания регистра с константой справа
		OT_MulTempConst, // Бинарная операция умножения регистра с константой
		OT_DivTempConstLeft, // Бинарная операция деления регистра с константой слева
		OT_DivTempConstRight, // Бинарная операция деления регистра с константой справа
		OT_LoadConst, // Запоминаем константу в регистр
		OT_AndTemps, // Логическая операция И с регистрами
		OT_OrTemps, // Логическая операция ИЛИ с регистрами
		OT_XorTemps, // Взаимоисключающее ИЛИ для регистров
		OT_AndTempConst, // Логическая операция И с регистром и константой
		OT_OrTempConst, // Логическая операция ИЛИ с регистром и константой
		OT_XorTempConst, //  Взаимоисключающее ИЛИ для регистра и конмтанты
		OT_CMP, // сравнение регистров
		OT_CMPC, // сравнение с константой 
		OT_JMP, // безусловный прыжок
		OT_JE,  // нуль или равно // ZF = 1
		OT_JNE, // не нуль или не равно // ZF = 0
		OT_JG,	// больше / не меньше и не равно // ZF = 0 и SF = OF
		OT_JGE, // JNL больше или равно / не меньше // SF = OF
		OT_JL,	// JNGE меньше / не больше и не равно // SF != OF
		OT_JLE,	// JNG меньше или равно / не больше	// ZF = 1 или SF != OF
		OT_Movem, //MOVE from MEM to MEM 
		OT_Store, // Store
		OT_StoreConst, // Store c одной константой
		OT_StoreTemp, // Store c одним Temp
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion