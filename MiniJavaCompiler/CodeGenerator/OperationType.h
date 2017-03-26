#pragma once

#include <string>

namespace CodeGeneartion {

	enum TOperationType {
		OT_None, // Не используется!
		OT_Move, // Должно использоваться отдельно, для распределенияр регистров
		OT_MemFramePointerPlusConst, // Обращеине к ISP + константа
		OT_MemRegPlusConst, // Обращеине регистр + константа
		OT_MemRegMinusConst, // Обращеине регистр - константа
		OT_MemConstMinusReg, // Обращеине константа - регистр
		OT_MemRegMulConst, // Обращеине регистр * константа
	};

	std::wstring GetOperationString( TOperationType type );

} // namespace CodeGeneartion