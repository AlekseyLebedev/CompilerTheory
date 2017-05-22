#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

#include "Printer.h"
#include "CodeGeneratorVisitor.h"
#include "..\RegisterAllocator\RegisterAllocator.h"

using namespace IRTree;

namespace CodeGeneration
{
	CAssemlerCodePrinter::CAssemlerCodePrinter( const std::wstring& filename ) : output( filename + L".txt" )
	{
	}

	CAssemlerCodePrinter::~CAssemlerCodePrinter()
	{
		assert( !output.is_open() );
	}

	void CAssemlerCodePrinter::PrintBlock( CSharedPtrVector<IInstruction>& code, std::map<int, int>& reg )
	{
		for( size_t i = 0; i < code.size(); i++ ) {
			output << code[i]->ToCode( reg ) << std::endl;
		}
	}

	void CAssemlerCodePrinter::Close()
	{
		output.close();
	}


	void HandleBlocks( std::list<std::pair<std::shared_ptr<IRTree::IRTStatement>, std::shared_ptr<IRTree::CFrame>>>& basisBlocks, int& fileIndex )
	{
		CodeGeneration::CAssemlerCodePrinter assemblePrinter( L"code-" + std::to_wstring( fileIndex++ ) );
		CFrame* lastFrame = 0;
		std::vector<CSharedPtrVector<IInstruction>> commands;
		for( std::list<std::pair<std::shared_ptr<IRTStatement>, std::shared_ptr<CFrame>>>::iterator block = basisBlocks.begin();
			block != basisBlocks.end(); ++block ) {
			CCodeGeneratorVisitor codeGeneratorVisitor;
			codeGeneratorVisitor.SetFrame( block->second );
			codeGeneratorVisitor.Visit( std::dynamic_pointer_cast<IRTSSeq>(block->first).get() );
			CodeGeneration::CSharedPtrVector<CodeGeneration::IInstruction> code = codeGeneratorVisitor.GetCode();
			if( lastFrame != block->second.get() ) {
				lastFrame = block->second.get();
				commands.push_back( CSharedPtrVector<IInstruction>() );
			}
			for( size_t i = 0; i < code.size(); i++ ) {
				commands.back().push_back( code[i] );
			}
		}
			
		for( size_t i = 0; i < commands.size(); i++ ) {
			bool isRepeat = true;
			while( isRepeat ) {
				isRepeat = false;
				
				RegAlloc::RegisterAllocator regAlloc;
				regAlloc.initialisation( commands[i] );
				int result = regAlloc.work();
				if( result == -1 ) {
					assemblePrinter.PrintBlock( commands[i], regAlloc.getColors() );
				} else {

#define DEBUG_MODE
#ifdef DEBUG_MODE
					std::cerr << "Цветов не хватает!\n";
					// exit(1);
					assemblePrinter.PrintBlock( commands[i], regAlloc.getColors() ); //or
					break; // or
#endif //DEBUG_MODE

					isRepeat = true;
					
					// В result -- переменная, на которой произошла ошибка (которой не хватило цвета)
				
					// Нужно: Записать в локальную переменную на стеке...

					// -------
					// start
					// -------

					// Ищем блок, в котором произошла ошибка.
					int idx = i;
					auto block = basisBlocks.begin();
					while( idx > 0 ) {
						++block;
						--idx;
					}

					auto frame = block->second;
					
					// Берём информацию о "плохой" переменной.
					std::shared_ptr<IAccess> info = frame->GetDataInfo( result );
					
					// Меняем frame...
					int frameNumber = frame->InsertTemp( result, info );
					
					// Перенаправить команды load и read, дабы разгрузить упоминание переменной

					// Генеририруем новый код с новым темпом.
					CCodeGeneratorVisitor codeGeneratorVisitor;
					codeGeneratorVisitor.SetFrame( frame );
					CodeGeneration::CSharedPtrVector<CodeGeneration::IInstruction> code = codeGeneratorVisitor.GetCode();

					std::shared_ptr<COperation> operation = std::make_shared<COperation>( OT_StoreToFramePointerPlusConst );
					int offset = 4 * frame->VariableOffset() + 1 + frameNumber; // Формула от Лёши
					operation->GetConstants().push_back( offset );
					code.push_back( operation );

					// Поиск упоминаний, где перенаправить вывод
					// operation = std::make_shared<COperation>( OT_MoveFramePointerPlusConstToMem );
					// operation->GetArguments().push_back( ??? );
					// operation->GetConstants().push_back( ??? );

					commands[i] = code;

					// -------
					// end
					// -------
				}
			}
		}

		assemblePrinter.Close();
	}

} // namespace CodeGeneration
