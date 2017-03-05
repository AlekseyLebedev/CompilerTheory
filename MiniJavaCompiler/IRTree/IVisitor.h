#pragma once

namespace IRTree {
	class IRTExpList;

	// Expressions
	class IRTExpression;
	class IRTEConst;
	class IRTEConstBool;
	class IRTEName;
	class IRTETemp;
	class IRTEBinop;
	class IRTEMem;
	class IRTECall;
	class IRTEEseq;

	// Statements
	class IRTStatement;
	class IRTSMove;
	class IRTSExp;
	class IRTSJump;
	class IRTSCjump;
	class IRTSSeq;
	class IRTSLabel;
	class IAccess;
	class IVisitor {
	public:
		virtual void Visit( const IRTExpList* node ) = 0;

		// Expressions
		virtual void Visit( const IRTEConst* node ) = 0;
		virtual void Visit( const IRTEConstBool* node ) = 0;
		virtual void Visit( const IRTEName* node ) = 0;
		virtual void Visit( const IRTETemp* node ) = 0;
		virtual void Visit( const IRTEBinop* node ) = 0;
		virtual void Visit( const IRTEMem* node ) = 0;
		virtual void Visit( const IRTECall* node ) = 0;
		virtual void Visit( const IRTEEseq* node ) = 0;

		// Statements
		virtual void Visit( const IRTSMove* node ) = 0;
		virtual void Visit( const IRTSExp* node ) = 0;
		virtual void Visit( const IRTSJump* node ) = 0;
		virtual void Visit( const IRTSCjump* node ) = 0;
		virtual void Visit( const IRTSSeq* node ) = 0;
		virtual void Visit( const IRTSLabel* node ) = 0;

		virtual void Visit( const IAccess* node ) = 0;
	};
}