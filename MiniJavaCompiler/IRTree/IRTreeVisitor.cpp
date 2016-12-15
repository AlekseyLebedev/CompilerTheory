#include "IRTreeVisitor.h"

IRTree::IRTreeVisitor::IRTreeVisitor( const std::string& outputIRTFileName )
{
    graphvizOutputFile = std::ofstream( outputIRTFileName );
}

IRTree::IRTreeVisitor::~IRTreeVisitor()
{
    graphvizOutputFile.close();
}

void IRTree::IRTreeVisitor::Visit( const IRTExpList* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTEConst* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTEName* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTETemp* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTEBinop* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTEMem* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTECall* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTEEseq* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSMove* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSExp* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSJump* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSCjump* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSSeq* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSLabel* node )
{
    visitNode();

    // TO DO

    leaveNode();
}

void IRTree::IRTreeVisitor::visitNode()
{
    // TO DO
}

void IRTree::IRTreeVisitor::leaveNode()
{
    // TO DO
}
