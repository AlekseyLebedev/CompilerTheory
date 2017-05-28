#pragma once

#include <memory>
#include <map>
#include <list>
#include <string>
#include <fstream>
#include "Instruction.h"

#include "..\IRTree\Frame.h"
#include "..\IRTree\IRTStatement.h"

namespace CodeGeneration
{
	class CAssemlerCodePrinter {
	public:
		CAssemlerCodePrinter( const std::wstring& filename );
		~CAssemlerCodePrinter();

		void PrintFrame( CSharedPtrVector<IInstruction>& code, std::map<int, int>& colors, std::shared_ptr<IRTree::CFrame>& frame );

		void Close();

	private:
		std::wofstream output;
	};

	//-----------------------------------------------------------------------------------------------------------------

	class CAssemblerCodeCreator {
	public:
		CAssemblerCodeCreator( std::list<std::pair<std::shared_ptr<IRTree::IRTStatement>, std::shared_ptr<IRTree::CFrame>>>& basisBlocks, std::wstring& filename );
		void AllocateRegistersAndPrint();


	private:
		CodeGeneration::CAssemlerCodePrinter assemblePrinter;
		std::vector<CSharedPtrVector<IInstruction>> commands;
		CSharedPtrVector<IRTree::CFrame> frames;

		void addTempToStack( int blockIndex, std::shared_ptr<CTemp>& problemTemp );
	};

	//-----------------------------------------------------------------------------------------------------------------

	inline bool IsReadOperation( std::shared_ptr<COperation>& operation, int index )
	{
		// assert( index < operation->GetArguments().size() ); // Бесполезен, но верен
		int argcount = operation->GetArguments().size();
		switch( argcount ) {
			case 2:
				switch( operation->GetType() ) {
					case OT_CMP:
					case OT_Movem:
					case OT_Store:
					case OT_StoreTemp:
						return true;
						// case OT_...:
						// 	return false;
					default:
						return index > 0;
				}
				break;
			case 3:
				return index > 0;
				break;
			case 1:
				switch( operation->GetType() ) {
					case OT_Push:
					case OT_StoreToFramePointerPlusConst:
					case OT_CMPC:
					case OT_MoveMemToEax:
					case OT_MoveTempToEax:
					case OT_MoveFramePointerPlusConstToMem:
					case OT_MoveFramePointerPlusConstToEax:
					case OT_MoveMemToFramePointerPlusConst:
						return true;
					case OT_Pop:
					case OT_MemFramePointerPlusConst:
					case OT_Call:
					case OT_LoadConst:
					case OT_MemConst:
						return false;
					default:
						// ДОБАВЬ В ВЕТКИ ВЫШЕ!!!!!!
						assert( false );
						break;
				}
			default:
				return false;
		}
	}
} // namespace CodeGeneration
