#pragma once
#include <memory>
#include <map>
#include <list>
#include "IRTree\StatementClasses\IRTSSeq.h"

using namespace IRTree;

class CGenerator {

private:
	// храним список всех блоков в виде указателей на канонические деревья
	std::list<std::shared_ptr<IRTSSeq> > basicBlocks;
};