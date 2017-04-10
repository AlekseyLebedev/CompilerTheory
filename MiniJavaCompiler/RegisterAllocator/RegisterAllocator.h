#pragma once

#include <string>
#include <vector>
#include <set>
#include <iostream>

namespace RegAlloc {

	class RegisterAllocator {

	public:

		void initialisation();

		void work();

	private:

		// Здесь хранятся номера переменных, "живых" на каком-то входящем ребре в вершину N.
		std::vector<std::set<int>> live_in;
		// Здесь хранятся номера переменных, "живых" на каком-то исходящем ребре из вершины N.
		std::vector<std::set<int>> live_out;

		//Всем переменным дадим идентификаторы для удобства работы.
		// Здесь хранятся номера переменных, определяемых в вершине N.
		std::vector<std::set<int>> def;
		// Здесь хранятся номера переменных, используемых в вершине N.
		std::vector<std::set<int>> use;

		// Здесь хранятся номера вершин, куда следует ребро из вершины N.
		std::vector<std::set<int>> out_edges;
		// Здесь хранятся номера вершин, откуда следует ребро в вершину N.
		std::vector<std::set<int>> in_edges;

		void generateTempExample();

		void printStateTempExample( unsigned int numberOfVertexes );

	};
}
