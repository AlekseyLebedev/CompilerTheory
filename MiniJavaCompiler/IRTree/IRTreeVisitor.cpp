#include <cassert>
#include "IRTreeVisitor.h"
#include "IRTreeAllClasses.h"

const std::string SOMETEXT = "NODELABEL";

IRTree::IRTreeVisitor::IRTreeVisitor()
	: currentNodeID( 0 ), numberOfVisitedNodes( 0 ), lastNodeID( 0 )
{
	nodesStack.push( currentNodeID );
	nodeLables.insert( std::make_pair( currentNodeID, "Frame" ) );
}

IRTree::IRTreeVisitor::~IRTreeVisitor()
{
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

	switch( node->GetBinop() ) {
		case BINOP_PLUS:
			nodeLables.insert( std::make_pair( currentNodeID, "PLUS" ) );
			break;
		case BINOP_MINUS:
			nodeLables.insert( std::make_pair( currentNodeID, "MINUS" ) );
			break;
		case BINOP_MUL:
			nodeLables.insert( std::make_pair( currentNodeID, "MUL" ) );
			break;
		case BINOP_DIV:
			nodeLables.insert( std::make_pair( currentNodeID, "DIV" ) );
			break;
		default:
			assert( false );
			break;
	}

	node->GetLeft()->Accept( this );
	node->GetRight()->Accept( this );

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

	nodeLables.insert( std::make_pair( currentNodeID, "CALL" ) );
	node->GetFunc()->Accept( this );

	if( node->GetArgs() ) {
		node->GetArgs()->Accept( this );
	}

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

	nodeLables.insert( std::make_pair( currentNodeID, "JUMP" ) );

	unsigned int tempNode = createNode();
	nodeLables.insert( std::make_pair( tempNode, "LABEL " + node->GetLabel()->GetName() ) );
	addEdge( currentNodeID, tempNode );

	leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSCjump* node )
{
	visitNode();

	nodeLables.insert( std::make_pair( currentNodeID, "CJUMP" ) );

	unsigned int tempNode = createNode();

	switch( node->GetRelop() ) {
		case CJUMP_EQ:
			nodeLables.insert( std::make_pair( currentNodeID, "==" ) );
			break;
		case CJUMP_GE:
			nodeLables.insert( std::make_pair( currentNodeID, ">=" ) );
			break;
		case CJUMP_GT:
			nodeLables.insert( std::make_pair( currentNodeID, ">" ) );
			break;
		case CJUMP_LE:
			nodeLables.insert( std::make_pair( currentNodeID, "<=" ) );
			break;
		case CJUMP_LT:
			nodeLables.insert( std::make_pair( currentNodeID, "<" ) );
			break;
		case CJUMP_NE:
			nodeLables.insert( std::make_pair( currentNodeID, "!=" ) );
			break;
		default:
			assert( false );
			break;
	}

	addEdge( currentNodeID, tempNode );

	node->GetExpLeft()->Accept( this );
	node->GetExpRight()->Accept( this );

	// left label, true
	tempNode = createNode();
	nodeLables.insert( std::make_pair( tempNode, "LABEL " + node->GetLabelLeft()->GetName() ) );
	addEdge( currentNodeID, tempNode );

	// right label, false
	tempNode = createNode();
	nodeLables.insert( std::make_pair( tempNode, "LABEL " + node->GetLabelRight()->GetName() ) );
	addEdge( currentNodeID, tempNode );

	leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSSeq* node )
{
	visitNode();

	nodeLables.insert( std::make_pair( currentNodeID, "SEQ" ) );
	// left
	node->GetStmLeft()->Accept( this );
	// right
	if( node->GetStmRight() )
		node->GetStmRight()->Accept( this );

	leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IRTSLabel* node )
{
	visitNode();

	nodeLables.insert( std::make_pair( currentNodeID, "LABEL " + node->GetLabel()->GetName() ) );

	leaveNode();
}

void IRTree::IRTreeVisitor::Visit( const IAccess* node )
{
	visitNode();

	nodeLables.insert( std::make_pair( currentNodeID, "ACCESS " + node->GetName() ) );

	leaveNode();
}

void IRTree::IRTreeVisitor::Start( const std::string & filename )
{
	graphvizOutputFile = std::ofstream( filename );
}

void IRTree::IRTreeVisitor::Close()
{
	writeGraphToFile();
	graphvizOutputFile.close();
}

void IRTree::IRTreeVisitor::visitNode()
{
	lastNodeID = currentNodeID;
	currentNodeID = ++numberOfVisitedNodes;
	nodesStack.push( currentNodeID );
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

unsigned int IRTree::IRTreeVisitor::createNode()
{
	return (++numberOfVisitedNodes);
}
