#include "RegisterAllocator.h"
#include "..\CodeGenerator\CodeCreator.h"

#define DYNAMIC_CAST std::dynamic_pointer_cast

namespace RegAlloc {

	void RegisterAllocator::Initialisation()
	{

		// temporary
		// generateTempExample();

	}

	using namespace CodeGeneration;

	// Должно быть:
	void RegisterAllocator::Initialisation( CSharedPtrVector<IInstruction>& code )
	{

		numberOfVerteces = code.size();

		out_edges.resize( numberOfVerteces );
		in_edges.resize( numberOfVerteces );

		def.resize( numberOfVerteces );
		use.resize( numberOfVerteces );

		isMove.resize( numberOfVerteces );

		live_in.resize( numberOfVerteces );
		live_out.resize( numberOfVerteces );

		for( unsigned int codeLineIndex = 0; codeLineIndex < numberOfVerteces; ++codeLineIndex ) {
			std::shared_ptr<COperation> operation = DYNAMIC_CAST<COperation>( code[codeLineIndex] );
			if( operation != 0 ) {
				if( DYNAMIC_CAST<CCallOperation>( operation ) == 0 ) {
					// initialisation out_edges && in_edges
					CSharedPtrVector<CLabel> jumpPoints = operation->GetJumpPoints();
					for( unsigned int jump = 0; jump < jumpPoints.size(); ++jump ) {
						// Нужно привести jumpPoints[jump] к числу, то есть взять номер "строки", куда произойдёт переход.
						// jumpPoints[jump] => index
						// Поиск куда прыгаем
						bool find = false;
						for( size_t i = 0; i < numberOfVerteces; i++ ) {
							if( std::shared_ptr<CLabelDefinition> label = DYNAMIC_CAST<CLabelDefinition>( code[i] ) ) {
								if( jumpPoints[jump]->GetName() == label->GetLabel()->GetName() ) {
									out_edges[codeLineIndex].insert( i );
									in_edges[i].insert( codeLineIndex );
									find = true;
									break;
								}
							}
						}
						assert( find );
					}
				} else {
					assert( operation->GetArguments().size() == 1 );
					constraints[operation->GetArguments()[0]->GetName()] = 0; // Результат CALL всегда в %eax
				}

				// Поиск следующей операции
				int j = codeLineIndex + 1;
				while( j < numberOfVerteces && DYNAMIC_CAST<COperation>( code[j] ) == 0 ) {
					++j;
				}
				if( j < numberOfVerteces ) {
					out_edges[codeLineIndex].insert( j );
					in_edges[j].insert( codeLineIndex );
				}

				// initialisation def
				CSharedPtrVector<CTemp> defined = operation->GetDefinedTemps();
				for( unsigned int argIndex = 0; argIndex < defined.size(); ++argIndex ) {
					// Получить идентификатор переменной:
					// defined[argIndex] => variable
					if( !CodeGeneration::IsReadOperation( operation, argIndex ) ) {
						def[codeLineIndex].insert( defined[argIndex]->GetName() );
					}
				}

				// initialisation use
				CSharedPtrVector<CTemp> arguments = operation->GetArguments();
				for( unsigned int argIndex = 0; argIndex < arguments.size(); ++argIndex ) {
					// Получить идентификатор переменной:
					// arguments[argIndex] => variable
					if( CodeGeneration::IsReadOperation( operation, argIndex ) ) {
						int name = arguments[argIndex]->GetName();
						use[codeLineIndex].insert( name );
						temps[name] = arguments[argIndex];
					}
				}

				// initialisation isMove
				isMove[codeLineIndex] = (DYNAMIC_CAST<CMoveOperation>( code[codeLineIndex] ) != 0);
			}
		}
	}

	std::shared_ptr<CTemp> RegisterAllocator::Work()
	{

		createTableWithLifeTime();
		createInteractionGraph();

		doSomethingWithInteractionGraph();

		removeLoops();
		return simplify( 5 );
	}

	std::map<int, int>& RegisterAllocator::GetColors()
	{
		return colors;
	}

	void RegisterAllocator::createTableWithLifeTime()
	{

		for( unsigned int i = 0; i < numberOfVerteces; ++i ) {
			for( auto iter = use[i].begin(); iter != use[i].end(); ++iter ) {
				if( live_in[i].find( *iter ) == live_in[i].end() ) {
					live_in[i].insert( *iter );
				}
			}
		}

		unsigned int i = 0;
		bool isEnd = true;
		while( true ) {

			//out
			for( auto iterEdges = out_edges[i].begin(); iterEdges != out_edges[i].end(); ++iterEdges ) {
				for( auto iterIn = live_in[*iterEdges].begin(); iterIn != live_in[*iterEdges].end(); ++iterIn ) {
					if( live_out[i].find( *iterIn ) == live_out[i].end() ) {
						live_out[i].insert( *iterIn );
						isEnd = false;
					}
				}
			}

			//in
			std::set<int> variables;
			for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
				variables.insert( *iter );
			}
			for( auto iter = def[i].begin(); iter != def[i].end(); ++iter ) {
				if( variables.find( *iter ) != variables.end() ) {
					variables.erase( *iter );
				}
			}
			for( auto iter = variables.begin(); iter != variables.end(); ++iter ) {
				if( live_in[i].find( *iter ) == live_in[i].end() ) {
					live_in[i].insert( *iter );
					isEnd = false;
				}
			}

			++i;
			if( i == numberOfVerteces ) {
				if( isEnd ) {
					break;
				}
				//printState(numberOfVerteces);
				isEnd = true;
				i = 0;
			}
		}
		//printState();
	}

	void RegisterAllocator::createInteractionGraph()
	{
		for( unsigned int i = 0; i < numberOfVerteces; ++i ) {
			for( auto defined = def[i].begin(); defined != def[i].end(); ++defined ) {
				for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
					if( isMove[i] ) {
						if( *defined != *iter ) {
							interactionGraph.insert( std::make_pair( std::make_pair( *defined, *iter ), true ) );
							interactionGraph.insert( std::make_pair( std::make_pair( *iter, *defined ), true ) );
						}
					} else {
						if( interactionGraph.find( std::make_pair( std::make_pair( *defined, *iter ), true ) ) == interactionGraph.end() ) {
							interactionGraph.insert( std::make_pair( std::make_pair( *defined, *iter ), false ) );
							interactionGraph.insert( std::make_pair( std::make_pair( *iter, *defined ), false ) );
						}
					}
				}
			}
		}
	}

	void RegisterAllocator::removeLoops()
	{
		std::vector<std::pair<std::pair<int, int>, bool>> loops;
		for( auto iter = interactionGraph.begin(); iter != interactionGraph.end(); iter++ ) {
			auto node = iter->first;
			if( node.first == node.second ) {
				loops.push_back( *iter );
			}
		}
		for( int i = 0; i < loops.size(); i++ ) {
			interactionGraph.erase( loops[i] );
		}
	}

	std::shared_ptr<CTemp> RegisterAllocator::simplify( unsigned int numberOfColors )
	{
		int answer = -1;

		// Для подсчёта соседей.
		std::map<int, int> numbersOfEdges;
		//Стек для алгоритма раскраски, bool -- для move-инструкций (если делать оптимизацию с ними).
		std::stack<std::pair<int, bool>> candidates; // кандидаты на отправку в стек
		std::stack<std::pair<int, bool>> tempStack; // вершинины с кол-вом соседей, меньшим кол-ва цветов
		std::vector<int> colored;

		std::set<std::pair<std::pair<int, int>, bool>> interactionGraphCopy = interactionGraph;

		for( auto iter = interactionGraphCopy.begin(); iter != interactionGraphCopy.end(); ++iter ) {
			auto vertex = numbersOfEdges.find( iter->first.first );
			int count = 0;
			if( vertex != numbersOfEdges.end() ) {
				count = vertex->second;
				numbersOfEdges.erase( vertex );
			}
			numbersOfEdges.insert( std::make_pair( iter->first.first, count + 1 ) );
		}

		bool isAll = true;
		int tempsCount = numbersOfEdges.size();

		for( unsigned int i = 0; i < tempsCount; ++i ) {
			int minNumberOfEdges = tempsCount;
			int name;
			for( auto iter = numbersOfEdges.begin(); iter != numbersOfEdges.end(); ++iter ) {
				if( iter->second < minNumberOfEdges ) {
					minNumberOfEdges = iter->second;
					name = iter->first;
				}
			}

			if( minNumberOfEdges < numberOfColors ) {
				if( constraints.find( name ) != constraints.end() ) {
					colored.push_back( name );
				} else {
					tempStack.push( std::make_pair( name, false ) );
				}
				auto iter = interactionGraphCopy.begin();
				while( interactionGraphCopy.begin() != interactionGraphCopy.end() ) {
					if( (iter->first.first == name) || (iter->first.second == name) ) {
						auto toDelete = iter;
						++iter;
						interactionGraphCopy.erase( toDelete );
					} else {
						++iter;
					}
					if( iter == interactionGraphCopy.end() ) {						
						break;
					}
				}
				numbersOfEdges.erase(name);
			} else {
				for( auto iter = numbersOfEdges.begin(); iter != numbersOfEdges.end(); ++iter ) {
					if( constraints.find( iter->first ) != constraints.end() ) {
						colored.push_back( iter->first );
					} else {
						candidates.push( std::make_pair( iter->first, true ) );
					}
				}
				numbersOfEdges.clear();
				break;
			}
		}

		// Сперва красим предопределенные вершины 
		for( int i = 0; i < colored.size(); i++ ) {
			int color = constraints.find( colored[i] )->second;
			std::vector<int> neighboors;
			for( auto iter = interactionGraph.begin(); iter != interactionGraph.end(); ++iter ) {
				if( iter->first.first == colored[i] ) {
					neighboors.push_back( iter->first.second );
				}
			}

			for( int j = 0; j < neighboors.size(); j++ ) {
				if( constraints.find( neighboors[j] ) != constraints.end()
					&& constraints.find( neighboors[j] )->second == color ) {
					answer = colored[i];
					return answer < 0 ? 0 : temps[answer];
				}
			}
			colors.insert( std::make_pair( colored[i], constraints.find( colored[i] )->second ) );
		}

		// Красим жадно те вершины, у которых мало соседей
		while( !tempStack.empty() ) {
			auto top = tempStack.top();
			tempStack.pop();
			std::vector<int> neighboors;
			for( auto iter = interactionGraph.begin(); iter != interactionGraph.end(); ++iter ) {
				if( iter->first.first == top.first ) {
					neighboors.push_back( iter->first.second );
				}
			}

			std::set<int> availableNumbers;
			for( int i = 0; i < numberOfColors; ++i ) {
				availableNumbers.insert( i );
			}

			for( unsigned i = 0; i < neighboors.size(); ++i ) {
				auto neighboor = colors.find( neighboors[i] );
				if( neighboor != colors.end() ) {
					availableNumbers.erase( neighboor->second );
				}
			}

			colors.insert( std::make_pair( top.first, *availableNumbers.begin() ) );
		}


		// Пытаемся покрасить кандидатов
		while( !candidates.empty() ) {
			auto top = candidates.top();
			candidates.pop();
			std::vector<int> neighboors;
			for( auto iter = interactionGraph.begin(); iter != interactionGraph.end(); ++iter ) {
				if( iter->first.first == top.first ) {
					neighboors.push_back( iter->first.second );
				}
			}

			std::set<int> availableNumbers;
			for( int i = 0; i < numberOfColors; ++i ) {
				availableNumbers.insert( i );
			}

			for( unsigned i = 0; i < neighboors.size(); ++i ) {
				auto neighboor = colors.find( neighboors[i] );
				if( neighboor != colors.end() ) {
					availableNumbers.erase( neighboor->second );
				}
			}

			if( availableNumbers.begin() == availableNumbers.end() ) {

				// тут должен происходить сброс в стек
				// Смотри Printer.cpp, всё происходт там, тут лишь сообщается о пробемной переменной

				answer = top.first;
				break;
			}
			colors.insert( std::make_pair( top.first, *availableNumbers.begin() ) );
		}

		return answer < 0 ? 0 : temps[answer];
	}

	void RegisterAllocator::doSomethingWithInteractionGraph()
	{

		//for( auto iter = interactionGraph.begin(); iter != interactionGraph.end(); ++iter ) {
		//	std::cout << iter->first.first << " -> " << iter->first.second << '\n';
		//}

	}

	//void RegisterAllocator::generateTempExample()
	//{

	//	//////////////////
	//	// 0: a:= 0
	//	// 1: b:= a+1
	//	// 2: c:= c+b
	//	// 3: a:= b*2
	//	// 4: if a<N GOTO 2
	//	// 5: return c
	//	//
	//	// a - 0
	//	// b - 1
	//	// c - 2
	//	// 
	//	//////////////////

	//	numberOfVerteces = 6;

	//	out_edges.resize( numberOfVerteces );
	//	in_edges.resize( numberOfVerteces );

	//	def.resize( numberOfVerteces );
	//	use.resize( numberOfVerteces );

	//	out_edges[0].insert( 1 );
	//	out_edges[1].insert( 2 );
	//	out_edges[2].insert( 3 );
	//	out_edges[3].insert( 4 );
	//	out_edges[4].insert( 1 );
	//	out_edges[4].insert( 5 );

	//	in_edges[1].insert( 0 );
	//	in_edges[1].insert( 4 );
	//	in_edges[2].insert( 1 );
	//	in_edges[3].insert( 2 );
	//	in_edges[4].insert( 3 );
	//	in_edges[5].insert( 4 );

	//	def[0].insert( 0 );
	//	def[1].insert( 1 );
	//	def[2].insert( 2 );
	//	def[3].insert( 0 );

	//	use[1].insert( 0 );
	//	use[2].insert( 1 );
	//	use[2].insert( 2 );
	//	use[3].insert( 3 );
	//	use[4].insert( 0 );
	//	use[5].insert( 2 );

	//	isMove.resize( numberOfVerteces );
	//	isMove[0] = true;
	//	isMove[1] = true;
	//	isMove[2] = true;
	//	isMove[3] = true;
	//	isMove[4] = false;
	//	isMove[5] = false;

	//	live_in.resize( numberOfVerteces );
	//	live_out.resize( numberOfVerteces );
	//}

	void RegisterAllocator::printState()
	{
		//assert( false );
		std::cout << "\tuse\tdef\tin\tout\n";
		for( int i = 0; i < numberOfVerteces; ++i ) {
			std::cout << (i + 1) << '\t';
			for( auto iter = use[i].begin(); iter != use[i].end(); ++iter ) {
				std::cout << *iter << ' ';
			}
			std::cout << ";\t";
			for( auto iter = def[i].begin(); iter != def[i].end(); ++iter ) {
				std::cout << *iter << ' ';
			}
			std::cout << ";\t";
			for( auto iter = live_in[i].begin(); iter != live_in[i].end(); ++iter ) {
				std::cout << *iter << ' ';
			}
			std::cout << ";\t";
			for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
				std::cout << *iter << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
} // namespace RegAlloc
