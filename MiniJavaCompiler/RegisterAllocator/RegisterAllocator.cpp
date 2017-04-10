#include "RegisterAllocator.h"

namespace RegAlloc {

	void RegisterAllocator::initialisation() {

		//temporary
		generateTempExample();

	}

	void RegisterAllocator::work() {

		unsigned int numberOfVertexes = live_in.size();

		for( unsigned int i = 0; i < numberOfVertexes; ++i ) {
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
			std::set<int> variables;
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
			if( i == numberOfVertexes) {
				if( isEnd ) {
					break;
				}
				//printStateTempExample(numberOfVertexes);
				isEnd = true;
				i = 0;
			}
		}
		printStateTempExample(numberOfVertexes);
	}

	void RegisterAllocator::generateTempExample() {
		
		//////////////////
		// 0: a:= 0
		// 1: b:= a+1
		// 2: c:= c+b
		// 3:a:= b*2
		// 4: if a<N GOTO 2
		// 5: return c
		//
		// a - 0
		// b - 1
		// c - 2
		// 
		//////////////////

		const int numberOfVertixes = 6;

		out_edges.resize(numberOfVertixes);
		in_edges.resize(numberOfVertixes);

		def.resize(numberOfVertixes);
		use.resize(numberOfVertixes);

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

		def[0].insert(0);
		def[1].insert(1);
		def[2].insert(2);
		def[3].insert(0);

		use[1].insert(0);
		use[2].insert(1);
		use[2].insert(2);
		use[3].insert(1);
		use[4].insert(0);
		use[5].insert(2);

		live_in.resize(numberOfVertixes);
		live_out.resize(numberOfVertixes);
	}

	void RegisterAllocator::printStateTempExample( unsigned int numberOfVertexes ) {
		std::cout << "\tuse\tdef\tin\tout\n";
		for( int i = 0; i < numberOfVertexes; ++i ) {
			std::cout << (i+1) << '\t';
			for( auto iter = use[i].begin(); iter != use[i].end(); ++iter ) {
				std::cout << (*iter == 0 ? 'a' : (*iter == 1 ? 'b' : 'c'));
			}
			std::cout << '\t';
			for( auto iter = def[i].begin(); iter != def[i].end(); ++iter ) {
				std::cout << (*iter == 0 ? 'a' : (*iter == 1 ? 'b' : 'c'));
			}
			std::cout << '\t';
			for( auto iter = live_in[i].begin(); iter != live_in[i].end(); ++iter ) {
				std::cout << (*iter == 0 ? 'a' : (*iter == 1 ? 'b' : 'c'));
			}
			std::cout << '\t';
			for( auto iter = live_out[i].begin(); iter != live_out[i].end(); ++iter ) {
				std::cout << (*iter == 0 ? 'a' : (*iter == 1 ? 'b' : 'c'));
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
}
