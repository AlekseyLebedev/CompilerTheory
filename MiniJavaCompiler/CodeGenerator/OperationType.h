#pragma once

#include <string>

enum TOperationType {
	OT_None, // Не используется!
	OT_Move, // Должно использоваться отдельно, для распределенияр регистров
	OT_MemFramePointerPlusCont, // Обращеине к ISP + константа
	OT_AddConstToFirst // Добавление к первому аргументу и т.д.
};

std::wstring GetOperationString( TOperationType type );