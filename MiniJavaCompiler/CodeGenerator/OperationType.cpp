#include <cassert>

#include "OperationType.h"

namespace CodeGeneartion {

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
		default:
			assert( false );
			break;
	}
}

} // namespace CodeGeneartion