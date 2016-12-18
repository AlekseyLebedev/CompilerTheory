#pragma once
#include "..\IRTree\IRTreeVisitor.h"
#include "..\IRTree\INode.h"
#include "..\IRTree\IRTreeAllClasses.h"

typedef IRTree::IRTreeVisitor TVisitor;
typedef IRTree::INode TNode;
#include "BaseDotOutput.h"

using namespace IRTree;
namespace GraphvizOutput {

	class CIRTDotOutputVisitor : public IRTree::IVisitor, public CBaseDotOutput {
	public:
		CIRTDotOutputVisitor();
		virtual ~CIRTDotOutputVisitor();
		//virtual void Visit( IRTEBinop * ) override;
	};
}
