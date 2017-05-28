﻿#pragma once

#include <string>

namespace CodeGeneration {

	enum TOperationType {
		OT_None, // Не используется!
		OT_Move, // Должно использоваться отдельно, для распределенияр регистров
		OT_MemFramePointerPlusConst, // Обращение к ISP + константа
		OT_MemRegPlusConst, // Обращение регистр + константа
		OT_MemRegMinusConst, // Обращение регистр - константа
		OT_MemConstMinusReg, // Обращение константа - регистр
		OT_MemRegMulConst, // Обращение регистр * константа
		OT_MemConst, // Обращение в память по константe
		OT_MemReg, // Обращение в память по значению из регистра
		OT_Call, // Вызов функции
		OT_AddConstToFirst, // Добавление к первому аргументу и т.д.
		OT_AddTemps, // Бинарная операция сложения регистров
		OT_SubTemps, // Бинарная операция вычитания регистров
		OT_MulTemps, // Бинарная операция умножения регистров
		OT_DivTemps, // Бинарная операция деления регистров
		OT_AddTempConst, // Бинарная операция сложения регистра с константой
		OT_AddEspConst, // Бинарная операция прибавление константы к %esp
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
		OT_JumpNonZero, // ????????????????????????????????????????????????????????77
		OT_Movem, //MOVE from MEM to MEM 
		OT_MoveMemToFramePointerPlusConst, //MOVE from MEM to MEM(framepointer + const) 
		OT_MoveFramePointerPlusConstToMem, //MOVE from MEM to MEM(framepointer + const) 
		OT_MoveFramePointerPlusConstToEax, //MOVE from MEM to MEM(framepointer + const) 
		OT_MoveMemToEax, //MOVE from MEM to eax (return)
		OT_MoveTempToEax, //MOVE from MEM to eax (return)
		OT_Store, // Store
		OT_StoreToFramePointerPlusConst, // Store в память MEM(FramePointer + const )
		OT_StoreConst, // Store c одной константой
		OT_StoreTemp, // Store c одним Temp
		OT_Push, // Push на стэк
		OT_Pop, // Pop со стэка
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion