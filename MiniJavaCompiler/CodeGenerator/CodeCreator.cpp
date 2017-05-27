#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

#include "CodeCreator.h"
#include "CodeGeneratorVisitor.h"
#include "..\RegisterAllocator\RegisterAllocator.h"
#include "..\SymbolTable\ClassInfo.h"

using namespace IRTree;

namespace CodeGeneration
{
	CAssemlerCodeCreator::CAssemlerCodeCreator( const std::wstring& filename ) : output( filename + L".txt" )
	{
	}

	CAssemlerCodeCreator::~CAssemlerCodeCreator()
	{
		assert( !output.is_open() );
	}

	void CAssemlerCodeCreator::PrintBlock( CSharedPtrVector<IInstruction>& code, std::map<int, int>& reg )
	{
		for( size_t i = 0; i < code.size(); i++ ) {
			output << code[i]->ToCode( reg ) << std::endl;
		}
		//TODO
		output.flush();
	}

	void CAssemlerCodeCreator::Close()
	{
		output.close();
	}

	static inline bool isReadOperation( CSharedPtrVector<CTemp>& arguments, int index )
	{
		assert( index < arguments.size() );
		return index > 0;
	}

	static inline bool isCurrentTempReaded( CSharedPtrVector<CTemp>& arguments, int index, std::shared_ptr<CTemp>& temp )
	{
		return arguments[index] == temp &&  isReadOperation( arguments, index );
	}

	static inline bool isCurrentTempWrited( CSharedPtrVector<CTemp>& arguments, int index, std::shared_ptr<CTemp>& temp )
	{
		return arguments[index] == temp && (!isReadOperation( arguments, index ));
	}

	void HandleBlocks( std::list<std::pair<std::shared_ptr<IRTree::IRTStatement>, std::shared_ptr<IRTree::CFrame>>>& basisBlocks, int& fileIndex )
	{
		CodeGeneration::CAssemlerCodeCreator assemblePrinter( L"code-" + std::to_wstring( fileIndex++ ) );
		CFrame* lastFrame = 0;
		std::vector<CSharedPtrVector<IInstruction>> commands;
		CSharedPtrVector<CFrame> frames;
		for( std::list<std::pair<std::shared_ptr<IRTStatement>, std::shared_ptr<CFrame>>>::iterator block = basisBlocks.begin();
			block != basisBlocks.end(); ++block ) {
			CCodeGeneratorVisitor codeGeneratorVisitor;
			codeGeneratorVisitor.SetFrame( block->second );
			codeGeneratorVisitor.Visit( std::dynamic_pointer_cast<IRTSSeq>(block->first).get() );
			CodeGeneration::CSharedPtrVector<CodeGeneration::IInstruction> code = codeGeneratorVisitor.GetCode();
			if( lastFrame != block->second.get() ) {
				lastFrame = block->second.get();
				commands.push_back( CSharedPtrVector<IInstruction>() );
				frames.push_back( block->second );
			}
			for( size_t i = 0; i < code.size(); i++ ) {
				commands.back().push_back( code[i] );
			}
		}

		for( size_t blockIndex = 0; blockIndex < commands.size(); blockIndex++ ) {
			bool isRepeat = true;
			while( isRepeat ) {
				RegAlloc::RegisterAllocator regAlloc;
				regAlloc.Initialisation( commands[blockIndex] );
				std::shared_ptr<CTemp> problemTemp = regAlloc.Work();
				if( problemTemp == 0 ) {
					isRepeat = false;
					assemblePrinter.PrintBlock( commands[blockIndex], regAlloc.GetColors() );
				} else {
					isRepeat = true;
					// Test
					assemblePrinter.PrintBlock( commands[blockIndex], regAlloc.GetColors() );


					// В result -- переменная, на которой произошла ошибка (которой не хватило цвета)
					auto frame = frames[blockIndex];

					// Меняем frame...
					std::shared_ptr<CTemp> dublicateTemp = std::make_shared<CTemp>( frame->NewTemp() );
					std::shared_ptr<COperation> storeOperation = std::make_shared<COperation>( OT_StoreToFramePointerPlusConst );
					int offset = -frame->AllocatedMemory();
					frame->AddStackTemp(); // Иммено после offset
					storeOperation->GetConstants().push_back( offset );
					storeOperation->GetArguments().push_back( problemTemp );

					// Поиск упоминаний, где перенаправить вывод
					CSharedPtrVector<IInstruction>& code = commands[blockIndex];
					size_t size = code.size();
					int storeInsertIndex = -1;
					int loadInsertIndex = -1;
					for( size_t operationIndex = 0; operationIndex < size; ++operationIndex ) {
						auto operation = std::dynamic_pointer_cast<COperation>(code[operationIndex]);
						if( operation ) {
							// Обратный порядок важен!
							for( int i = operation->GetArguments().size() - 1; i >= 0; i-- ) {
								if( storeInsertIndex < 0 ) {

									if( isCurrentTempWrited( operation->GetArguments(), i, problemTemp ) ) {
										storeInsertIndex = operationIndex + 1; // после вставляем
									}

								} else {

									if( isCurrentTempWrited( operation->GetArguments(), i, problemTemp ) ) {
										if( loadInsertIndex == -1 ) {
											loadInsertIndex = -2; // Не надо читать, мы перезаписали
										}
										operation->GetArguments()[i] = dublicateTemp;
									}
									if( isCurrentTempReaded( operation->GetArguments(), i, problemTemp ) ) {
										if( loadInsertIndex == -1 ) {
											loadInsertIndex = operationIndex + 1; // здесь +1 т.к. уже сохранение вставлено, а выполняется до операции
										}
										operation->GetArguments()[i] = dublicateTemp;
									}
								}
							}

							if( storeInsertIndex >= 0 && storeInsertIndex <= operationIndex ) {
								for( size_t i = 0; i < operation->GetDefinedTemps().size(); i++ ) {
									assert( operation->GetDefinedTemps()[i] != problemTemp );
								}
							}
						}
					}

					assert( storeInsertIndex >= 0 );
					code.insert( code.begin() + storeInsertIndex, storeOperation );
					if( loadInsertIndex > 0 ) {
						std::shared_ptr<COperation> loadOperation = std::make_shared<COperation>( OT_MemFramePointerPlusConst );
						loadOperation->GetConstants().push_back( offset );
						loadOperation->GetArguments().push_back( dublicateTemp );
						loadOperation->GetDefinedTemps().push_back( dublicateTemp );
						code.insert( code.begin() + loadInsertIndex, loadOperation );
					}

				}
			}
		}

		assemblePrinter.Close();
	}

} // namespace CodeGeneration
