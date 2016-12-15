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
    //visitNode(); - вспомогательный

    const IRTExpression* head = node->GetHead();
    const IRTExpList* tail = node->GetTail();

    if( head ) {
        head->Accept( this );
    }

    if( tail ) {
        tail->Accept( this );
    }

    //leaveNode(); - вспомогательный
}

void IRTree::IRTreeVisitor::Visit( const IRTEConst* node )
{
    visitNode();

    nodeLables.insert( std::make_pair( currentNodeID, "CONST " + std::to_string( node->GetValue() ) ) );

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTEName* node )
{
    visitNode();

    nodeLables.insert( std::make_pair( currentNodeID, "NAME " + node->GetLabel()->GetName() ) );

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTETemp* node )
{
    visitNode();

    nodeLables.insert( std::make_pair( currentNodeID, "TEMP " + node->GetTemp()->GetName() ) );

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

    nodeLables.insert( std::make_pair( currentNodeID, "MEM" ) );
    node->GetExp()->Accept( this );

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

    nodeLables.insert( std::make_pair( currentNodeID, "ESEQ" ) );
    // left
    node->GetStm()->Accept( this );
    // right
    node->GetExp()->Accept( this );

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSMove* node )
{
    visitNode();

    nodeLables.insert( std::make_pair( currentNodeID, "MOVE" ) );
    // left
    node->GetExrDst()->Accept( this );
    // right
    node->GetExrSrc()->Accept( this );

    leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSExp* node )
{
    visitNode();

    nodeLables.insert( std::make_pair( currentNodeID, "EXP" ) );
    node->GetExp()->Accept( this );

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

    nodeLables.insert( std::make_pair( currentNodeID, "LABEL " + node->GetLabel()->GetName() ) );

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
