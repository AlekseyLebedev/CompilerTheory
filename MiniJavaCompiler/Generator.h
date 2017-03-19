#pragma once
#include <memory>
#include <map>
#include <list>
#include "IRTree\IRTreeAllClasses.h"
#include "IRTree\CodeFragment.h"

using namespace IRTree;

class CGenerator {
public:
	CGenerator( std::shared_ptr<IRTree::CCodeFragment>  theRoot ) : root ( theRoot ) {}
	void SetRoot( std::shared_ptr<IRTree::CCodeFragment>  theRoot );
	std::shared_ptr<IRTree::CCodeFragment>  GetRoot();


private:
	std::shared_ptr<IRTree::CCodeFragment>  root;

	// храним список всех блоков в виде указателей на канонические деревья
	std::list<std::shared_ptr<IRTSSeq> > basicBlocks;

};