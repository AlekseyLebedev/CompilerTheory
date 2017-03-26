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
				return L"MOVE ' [ifp+!]";
			case OT_MemConstMinusReg:
				return L"MOVE ' [! - ']";
			case OT_MemRegMinusConst:
				return L"MOVE ' [' - !]";
			case OT_MemRegPlusConst:
				return L"MOVE ' [' + !]";
			case OT_MemRegMulConst:
				return L"MOVE ' [' * !]";
			case OT_MemConst:
				return L"MOVE ' [!]";
			case OT_MemReg:
				return L"MOVE ' [']";
			case OT_Call:
				return L"CALL ^";
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
			case OT_SubTempConstRight:
				return L"SUBI  ' ' !";
			case OT_SubTempConstLeft:
				return L"SUBI  ' ! '";
			case OT_MulTempConst:
				return L"MULI  ' ' !";
			case OT_DivTempConstRight:
				return L"DIVI  ' ' !";
			case OT_DivTempConstLeft:
				return L"DIVI  ' ! '";
			case OT_LoadConst:
				return L"LOAD ' !";
			case OT_AndTemps:
				return L"AND ' '";
			case OT_OrTemps:
				return L"OR ' '";
			case OT_XorTemps:
				return L"XOR ' '";
			case OT_AndTempConst:
				return L"ANDI ' !";
			case OT_OrTempConst:
				return L"ORI ' !";
			case OT_XorTempConst:
				return L"XORI ' !";
			case OT_CMP:
				return L"CMP ' '";
			case OT_JMP:
				return L"JMP ^";
			case OT_JE:
				return L"JE ^";
			case OT_JNE:
				return L"JNE ^";
			case OT_JG:
				return L"JG ^";
			case OT_JGE:
				return L"JGE ^";
			case OT_JL:
				return L"JL ^";
			case OT_JLE:
				return L"JLE ^";
			default:
				assert( false );
				break;
		}
	}

} // namespace CodeGeneartion