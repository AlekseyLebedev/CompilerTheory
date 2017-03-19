#pragma once
#include <memory>
#include <map>
#include <list>
#include "IRTree\IRTreeAllClasses.h"

using namespace IRTree;

class CGenerator {
public:
	CGenerator( std::shared_ptr<IRTSSeq> theRoot ) : root ( theRoot ) {}
	void SetRoot( std::shared_ptr<IRTSSeq> root );
	std::shared_ptr<IRTSSeq> getRoot();


private:
	std::shared_ptr<IRTSSeq> root;

	// храним список всех блоков в виде указателей на канонические деревья
	std::list<std::shared_ptr<IRTSSeq> > basicBlocks;

};