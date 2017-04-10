#include "RegisterAllocator.h"

namespace RegAlloc {

	void RegisterAllocator::initialisation() {

		//temporary
		generateTempExample();

	}

	void RegisterAllocator::work() {

		createTableWithLifeTime();
		createInteractionGraph();
		doSomethingWithInteractionGraph();

	}

	void RegisterAllocator::createTableWithLifeTime() {

		for( unsigned int i = 0; i < numberOfVerteces; ++i ) {
			for( auto iter = use[i].begin(); iter != use[i].end(); ++iter ) {
				if( live_in[i].find(*iter) == live_in[i].end() ) {
					live_in[i].insert(*iter);
				}
			}
		}

		unsigned int i = 0;
		bool isEnd = true;
		while( true ) {
			
			//out
			for( auto iterEdges = out_edges[i].begin(); iterEdges != out_edges[i].end(); ++iterEdges ) {
				for( auto iterIn = live_in[*iterEdges].begin(); iterIn != live_in[*iterEdges].end(); ++iterIn ) {
					if( live_out[i].find(*iterIn) == live_out[i].end() ) {
						live_out[i].insert(*iterIn);
						isEnd = false;
					}
				}
			}

			//in
			std::set<std::string> variables;
			for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
				variables.insert(*iter);
			}
			for( auto iter = def[i].begin(); iter != def[i].end(); ++iter ) {
				if( variables.find(*iter) != variables.end() ) {
					variables.erase(*iter);
				}
			}
			for( auto iter = variables.begin(); iter != variables.end(); ++iter ) {
				if( live_in[i].find(*iter) == live_in[i].end() ) {
					live_in[i].insert(*iter);
					isEnd = false;
				}
			}

			++i;
			if( i == numberOfVerteces) {
				if( isEnd ) {
					break;
				}
				//printState(numberOfVerteces);
				isEnd = true;
				i = 0;
			}
		}
		printState();
	}

	void RegisterAllocator::createInteractionGraph() {
		for( unsigned int i = 0; i < numberOfVerteces; ++i ) {
			for( auto defined = def[i].begin(); defined != def[i].end(); ++defined ) {
				for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
					if( !isMove[i] || (*defined != *iter) ) {
						interactionGraph.insert(std::make_pair(*defined, *iter));
					}
				}
			}
			//if( isMove[i] ) {
			//	for( auto defined = def[i].begin(); defined != def[i].end(); ++defined ) {
			//		for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
			//			if( *defined != *iter ) {
			//				interactionGraph.insert(std::make_pair(*defined, *iter));
			//			}
			//		}
			//	}
			//} else {
			//	for( auto defined = def[i].begin(); defined != def[i].end(); ++defined ) {
			//		for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
			//			interactionGraph.insert(std::make_pair(*defined, *iter));
			//		}
			//	}
			//}
		}
	}

	void RegisterAllocator::doSomethingWithInteractionGraph() {

		for( auto iter = interactionGraph.begin(); iter != interactionGraph.end(); ++iter ) {
			std::cout << iter->first << " -> " << iter->second << '\n';
		}

	}

	void RegisterAllocator::generateTempExample() {
		
		//////////////////
		// 0: a:= 0
		// 1: b:= a+1
		// 2: c:= c+b
		// 3: a:= b*2
		// 4: if a<N GOTO 2
		// 5: return c
		//
		// a - 0
		// b - 1
		// c - 2
		// 
		//////////////////

		numberOfVerteces = 6;

		out_edges.resize(numberOfVerteces);
		in_edges.resize(numberOfVerteces);

		def.resize(numberOfVerteces);
		use.resize(numberOfVerteces);

		out_edges[0].insert(1);
		out_edges[1].insert(2);
		out_edges[2].insert(3);
		out_edges[3].insert(4);
		out_edges[4].insert(1);
		out_edges[4].insert(5);

		in_edges[1].insert(0);
		in_edges[1].insert(4);
		in_edges[2].insert(1);
		in_edges[3].insert(2);
		in_edges[4].insert(3);
		in_edges[5].insert(4);

		def[0].insert("a");
		def[1].insert("b");
		def[2].insert("c");
		def[3].insert("a");

		use[1].insert("a");
		use[2].insert("b");
		use[2].insert("c");
		use[3].insert("b");
		use[4].insert("a");
		use[5].insert("c");

		isMove.resize(numberOfVerteces);
		isMove[0] = true;
		isMove[1] = true;
		isMove[2] = true;
		isMove[3] = true;
		isMove[4] = false;
		isMove[5] = false;

		live_in.resize(numberOfVerteces);
		live_out.resize(numberOfVerteces);
	}

	void RegisterAllocator::printState() {
		std::cout << "\tuse\tdef\tin\tout\n";
		for( int i = 0; i < numberOfVerteces; ++i ) {
			std::cout << (i+1) << '\t';
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
}
