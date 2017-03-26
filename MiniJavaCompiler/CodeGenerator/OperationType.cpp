#include <cassert>

#include "OperationType.h"

namespace CodeGeneration {

	std::wstring GetOperationString( TOperationType type )
	{
		switch( type ) {
			case OT_None:
				assert( false );
				break;
			case OT_Move:
				return L"MOVE ' '";
			case OT_MemFramePointerPlusConst:
				return L"MOVE ' [isp+!]";
			case OT_AddTemps:
				return L"ADD  ' ' '";
			case OT_SubTemps:
				return L"SUB  ' ' '";
			case OT_MulTemps:
				return L"MUL  ' ' '";
			case OT_DivTemps:
				return L"DIV  ' ' '";
			case OT_AddTempConst:
				return L"ADDI  ' ' !";
			case OT_SubTempConst:
				return L"SUBI  ' ' !";
			case OT_MulTempConst:
				return L"MULI  ' ' !";
			case OT_DivTempConst:
				return L"DIVI  ' ' !";
			case OT_LoadConst:
				return L"LOAD ' !";
			default:
				assert( false );
				break;
		}
	}

} // namespace CodeGeneartion