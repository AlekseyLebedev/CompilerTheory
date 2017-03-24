#pragma once

enum TOperationType {
	OT_None, // Не используется!
	OT_Move, // Должно использоваться отдельно, для распределенияр регистров
	OT_AddConstToFirst // Добавление к первому аргументу и т.д.
};
