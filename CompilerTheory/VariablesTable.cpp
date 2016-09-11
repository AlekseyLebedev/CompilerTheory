#include "stdafx.h"
#include "VariablesTable.h"

FirstTask::VariablesTable::VariablesTable(const char* name, const int value,
	const VariablesTable* tail) : Name(name), Value(value), Tail(tail) {
}