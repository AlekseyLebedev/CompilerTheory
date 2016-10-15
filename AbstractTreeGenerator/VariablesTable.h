#pragma once
#include <string>
#include <map>

namespace FirstTask {
	struct VariablesTable {
		const std::string Name;
		const int Value;
		const VariablesTable* const Tail;
		const VariablesTable(const char* name, const int value,
			const VariablesTable* tail);
	};
}