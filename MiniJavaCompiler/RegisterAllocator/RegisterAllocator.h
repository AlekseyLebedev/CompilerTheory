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

		void Initialisation();
		void Initialisation( CSharedPtrVector<IInstruction>& code );

		//0 -- если всё ОК
		std::shared_ptr<CTemp> Work();

		std::map<int, int>& GetColors();

	private:

		unsigned int numberOfVerteces;
		// Здесь хранятся переменных, "живых" на каком-то входящем ребре в вершину N.
		std::vector<std::set<int>> live_in;
		// Здесь хранятся переменных, "живых" на каком-то исходящем ребре из вершины N.
		std::vector<std::set<int>> live_out;

		// Здесь хранятся переменные, определяемых в вершине N.
		std::vector<std::set<int>> def;
		// Здесь хранятся переменные, используемых в вершине N.
		std::vector<std::set<int>> use;

		// Здесь хранятся номера вершин, куда следует ребро из вершины N.
		std::vector<std::set<int>> out_edges;
		// Здесь хранятся номера вершин, откуда следует ребро в вершину N.
		std::vector<std::set<int>> in_edges;

		//Является ли N-ная вершина move-инструкцией.
		std::vector<bool> isMove;

		//Граф взаимодействия переменных.
		std::set<std::pair<std::pair<int, int>, bool>> interactionGraph;
		//Цвета a.k.a. номера.
		std::map<int, int> colors;
		// Map из номеров в темпы
		std::map<int, std::shared_ptr<CTemp> > temps;

		void createTableWithLifeTime();
		void createInteractionGraph();
		//-1 -- если всё ОК
		void removeLoops();
		std::shared_ptr<CTemp> simplify( unsigned int numberOfColors );
		void doSomethingWithInteractionGraph();

		//void generateTempExample();

		void printState();

	};
} // namespace RegAlloc
