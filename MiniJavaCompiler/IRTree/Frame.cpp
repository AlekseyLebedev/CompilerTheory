#include "Frame.h"
#include "IRTExpression.h"
#include "IRTLabel.h"
#include <memory>
#include <cassert>
#include "..\SymbolTable\ClassInfo.h"

namespace IRTree {

	CFrame::CFrame( int className, std::shared_ptr<Label> _label ) : className( className ), label( _label ),
		thisAccess( std::make_shared<IAccess>( ThisName, className, 2 * SymbolTable::CClassInfo::MachineWordSize, L"this" ) ),
		returnAccess( std::make_shared<IAccess>( ReturnName, className, 0, L"return" ) ), argumentCount( 0 ), variableCount( 0 ), tempCounter( 0 ),
		framePointerAccess( std::make_shared<IAccess>( FramePointerName, className, 0, L"framePointer" ) ), stackTempCounter( 0 )
	{
	}

	void CFrame::InsertVariable( int name, std::shared_ptr<IAccess> access, bool argument )
	{
		variables.insert( std::pair<int, std::shared_ptr<IAccess>>( name, access ) );
		if( argument ) {
			++argumentCount;
		} else {
			++variableCount;
		}
	}

	void CFrame::AddStackTemp()
	{
		stackTempCounter++;
	}

	std::shared_ptr<IAccess> CFrame::GetDataInfo( int name )
	{
		auto iter = variables.find( name );
		if( iter != variables.end() ) {
			return iter->second;
		} else {
			return 0;
		}
	}

	std::shared_ptr<Label> CFrame::GetLabel()
	{
		return label;
	}

	std::shared_ptr<IAccess> CFrame::GetThisAccess()
	{
		return thisAccess;
	}

	std::shared_ptr<IAccess> CFrame::GetReturnAccess()
	{
		return returnAccess;
	}

	std::shared_ptr<IAccess> CFrame::GetFramePointerAccess()
	{
		return framePointerAccess;
	}

	int CFrame::VariableOffset()
	{
		// 1 - т.к. еще не добавили
		return - (variableCount + 1) * SymbolTable::CClassInfo::MachineWordSize;
	}

	int CFrame::ArgumentOffset()
	{
		// Старый %EBP, Return adress, this (и 1, т.к. не добавили) - 3 (с 0 индексация)
		return (argumentCount + 3) * SymbolTable::CClassInfo::MachineWordSize;
	}

	int CFrame::NewTemp()
	{
		return tempCounter++;
	}

	int CFrame::AllocatedMemory()
	{
		return SymbolTable::CClassInfo::MachineWordSize * (variableCount + stackTempCounter);
	}

	const int CFrame::ThisName = -11;
	const int CFrame::ReturnName = -12;
	const int CFrame::FramePointerName = -14;
}