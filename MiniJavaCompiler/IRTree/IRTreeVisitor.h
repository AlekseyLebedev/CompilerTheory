#pragma once

#include "IRTreeClasses.h"

namespace IRTree {

	class IRTreeVisitor {
    public:

        virtual void Visit( const IRTExpList* node ) = 0;
        virtual void Visit( const IRTStmList* node ) = 0;

        // Expressions
        virtual void Visit( const IRTEConst* node ) = 0;
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

	};

}
