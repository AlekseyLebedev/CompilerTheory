#pragma once

#include <string>
#include <vector>
#include <set>
#include <iostream>

#include "..\CodeGenerator\CodeGeneratorVisitor.h"
#include "..\CodeGenerator\Instruction.h"

namespace RegAlloc {

	using CodeGeneration;

	class RegisterAllocator {

	public:

		void initialisation();
		void initialisation( CSharedPtrVector<CodeGeneration::IInstruction> code );

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

		std::set<std::pair<std::string, std::string>> interactionGraph;

		void createTableWithLifeTime();
		void createInteractionGraph();
		void doSomethingWithInteractionGraph();

		void generateTempExample();

		void printState();

	};
} // namespace RegAlloc
