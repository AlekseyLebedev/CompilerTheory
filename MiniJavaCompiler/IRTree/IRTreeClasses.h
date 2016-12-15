#pragma once

namespace IRTree {

    class IRTreeVisitor;
    
    class IRTBuilderVisitor;

    class IRTExpList;

    // Expressions
    class IRTExpression;
    class IRTEConst;
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

    // Что такое Temp ??? (См. презентацию.)
    class Temp;
    class Label;
}

#include "IRTreeVisitor.h"

#include "IRTBuilderVisitor.h"

#include "IRTConstants.h"

#include "IRTExpList.h"
#include "IRTExpression.h"
#include "IRTStatement.h"

#include "IRTLabel.h"
#include "IRTTemp.h"

#include "ExpressionClasses\IRTEConst.h"
#include "ExpressionClasses\IRTEName.h"
#include "ExpressionClasses\IRTETemp.h"
#include "ExpressionClasses\IRTEBinop.h"
#include "ExpressionClasses\IRTEMem.h"
#include "ExpressionClasses\IRTECall.h"
#include "ExpressionClasses\IRTEEseq.h"

#include "StatementClasses\IRTSMove.h"
#include "StatementClasses\IRTSMove.h"
#include "StatementClasses\IRTSExp.h"
#include "StatementClasses\IRTSJump.h"
#include "StatementClasses\IRTSCjump.h"
#include "StatementClasses\IRTSSeq.h"
#include "StatementClasses\IRTSLabel.h"
