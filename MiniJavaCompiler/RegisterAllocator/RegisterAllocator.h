#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <iostream>

#include "..\CodeGenerator\Generator.h"
#include "..\CodeGenerator\Instruction.h"

namespace RegAlloc {

	using namespace CodeGeneration;

	class RegisterAllocator {

	public:

		void initialisation();
		void initialisation( CSharedPtrVector<COperation> code );

		void work();

	private:

		unsigned int numberOfVerteces;
		// Здесь хранятся переменных, "живых" на каком-то входящем ребре в вершину N.
		std::vector<std::set<std::string>> live_in;
		// Здесь хранятся переменных, "живых" на каком-то исходящем ребре из вершины N.
		std::vector<std::set<std::string>> live_out;

		// Здесь хранятся переменные, определяемых в вершине N.
		std::vector<std::set<std::string>> def;
		// Здесь хранятся переменные, используемых в вершине N.
		std::vector<std::set<std::string>> use;

		// Здесь хранятся номера вершин, куда следует ребро из вершины N.
		std::vector<std::set<int>> out_edges;
		// Здесь хранятся номера вершин, откуда следует ребро в вершину N.
		std::vector<std::set<int>> in_edges;

		//Является ли N-ная вершина move-инструкцией.
		std::vector<bool> isMove;

		//Граф взаимодействия переменных.
		std::set<std::pair<std::pair<std::string, std::string>, bool>> interactionGraph;
		//Цвета a.k.a. номера.
		std::map<std::string, int> colors;

		void createTableWithLifeTime();
		void createInteractionGraph();
		void simplify( unsigned int numberOfColors );
		void doSomethingWithInteractionGraph();

		void generateTempExample();

		void printState();

	};
} // namespace RegAlloc
