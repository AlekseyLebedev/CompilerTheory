#include <cassert>

#include "OperationType.h"

std::wstring GetOperationString( TOperationType type )
{
	switch( type ) {
		case OT_None:
			assert( false );
			break;
		case OT_Move:
			return L"MOVE ' '";
		case OT_MemFramePointerPlusCont:
			return L"MOVE ' [isp+!]";
		default:
			assert( false );
			break;
	}
}
