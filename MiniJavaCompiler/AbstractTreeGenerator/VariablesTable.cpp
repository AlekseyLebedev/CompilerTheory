#include "VariablesTable.h"

AbstractTreeGenerator::VariablesTable::VariablesTable(const char* name, const int value,
	const VariablesTable* tail) : Name(name), Value(value), Tail(tail) {
}