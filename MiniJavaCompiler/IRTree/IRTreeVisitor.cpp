#include "IRTreeVisitor.h"

const std::string SOMETEXT = "NODELABEL";

IRTree::IRTreeVisitor::IRTreeVisitor( const std::string& outputIRTFileName )
    : currentNodeID( 0 ), numberOfVisitedNodes( 0 ), lastNodeID( 0 )
{
    graphvizOutputFile = std::ofstream( outputIRTFileName );
}

IRTree::IRTreeVisitor::~IRTreeVisitor()
{
    writeGraphToFile();

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
    lastNodeID = currentNodeID;

    nodesStack.push( currentNodeID = ++numberOfVisitedNodes );

    addEdge( lastNodeID, currentNodeID );
}

void IRTree::IRTreeVisitor::leaveNode()
{
    lastNodeID = currentNodeID;

    nodesStack.pop();

    currentNodeID = nodesStack.top();
}

void IRTree::IRTreeVisitor::addEdge( unsigned int from, unsigned int to )
{
    edges.push_back( std::make_pair( from, to ) );
}

void IRTree::IRTreeVisitor::writeGraphToFile()
{
    graphvizOutputFile << "digraph { \nnode [shape\"box\"]\n";

    // edges
    for( unsigned int i = 0; i < edges.size(); ++i ) {
        graphvizOutputFile << edges[i].first << " -> " << edges[i].second << "\n";
    }

    // nodes
    for( unsigned int i = 0; i < numberOfVisitedNodes; ++i ) {
        graphvizOutputFile << i << "[ label \"" << SOMETEXT << "\" ]\n";
    }

    graphvizOutputFile << "}\n";
}
