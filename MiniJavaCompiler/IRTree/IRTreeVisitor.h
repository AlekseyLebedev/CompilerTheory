#pragma once

#include <string>
#include <fstream>

#include "IRTreeClasses.h"

namespace IRTree {

	class IRTreeVisitor {
    public:

        IRTreeVisitor( const std::string& outputIRTFileName );
        ~IRTreeVisitor();   

        virtual void Visit( const IRTExpList* node );

        // Expressions
        virtual void Visit( const IRTEConst* node );
        virtual void Visit( const IRTEName* node );
        virtual void Visit( const IRTETemp* node );
        virtual void Visit( const IRTEBinop* node );
        virtual void Visit( const IRTEMem* node );
        virtual void Visit( const IRTECall* node );
        virtual void Visit( const IRTEEseq* node );

        // Statements
        virtual void Visit( const IRTSMove* node );
        virtual void Visit( const IRTSExp* node );
        virtual void Visit( const IRTSJump* node );
        virtual void Visit( const IRTSCjump* node );
        virtual void Visit( const IRTSSeq* node );
        virtual void Visit( const IRTSLabel* node );

    private:

        void visitNode();
        void leaveNode();

        std::ofstream graphvizOutputFile;

	};

}
