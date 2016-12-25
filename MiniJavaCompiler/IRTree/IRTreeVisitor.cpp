#include <cassert>
#include <sstream>
#include "IRTreeVisitor.h"
#include "IRTreeAllClasses.h"

namespace IRTree {

	IRTreeVisitor::IRTreeVisitor()
		: currentNodeID( 0 ), numberOfVisitedNodes( 0 ), lastNodeID( 0 )
	{
		nodesStack.push( currentNodeID );
		nodeLables.insert( std::make_pair( currentNodeID, "Frame" ) );
	}

	IRTreeVisitor::~IRTreeVisitor()
	{
	}

	void IRTreeVisitor::Visit( const IRTExpList* node )
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

	void IRTreeVisitor::Visit( const IRTEConst* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "CONST " + std::to_string( node->GetValue() ) ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEName* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "NAME " + node->GetLabel()->GetName() ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTETemp* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "TEMP " + node->GetTemp()->GetName() ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEBinop* node )
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
			case BINOP_AND:
				nodeLables.insert( std::make_pair( currentNodeID, "AND" ) );
				break;
			case CJUMP_LT:
				nodeLables.insert( std::make_pair( currentNodeID, "LESS" ) );
				break;
			case BINOP_MOD:
				nodeLables.insert( std::make_pair( currentNodeID, "MOD" ) );
				break;
			case BINOP_OR:
				nodeLables.insert( std::make_pair( currentNodeID, "OR" ) );
				break;
			default:
				assert( false );
				break;
		}

		node->GetLeft()->Accept( this );
		node->GetRight()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEMem* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "MEM" ) );
		node->GetExp()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTECall* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "CALL" ) );
		node->GetFunc()->Accept( this );

		if( node->GetArgs() ) {
			node->GetArgs()->Accept( this );
		}

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEEseq* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "ESEQ" ) );
		// left
		node->GetStm()->Accept( this );
		// right
		node->GetExp()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSMove* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "MOVE" ) );
		// left
		node->GetExrDst()->Accept( this );
		// right
		node->GetExrSrc()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSExp* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "EXP" ) );
		node->GetExp()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSJump* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, "JUMP" ) );

		unsigned int tempNode = createNode();
		nodeLables.insert( std::make_pair( tempNode, concat( "LABEL ", node->GetLabel()->GetName() ) ) );
		addEdge( currentNodeID, tempNode );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSCjump* node )
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
		nodeLables.insert( std::make_pair( tempNode, concat( "LABEL ", node->GetLabelLeft()->GetName() ) ) );
		addEdge( currentNodeID, tempNode );

		// right label, false
		tempNode = createNode();
		nodeLables.insert( std::make_pair( tempNode, concat( "LABEL ", node->GetLabelRight()->GetName() ) ) );
		addEdge( currentNodeID, tempNode );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSSeq* node )
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

	void IRTreeVisitor::Visit( const IRTSLabel* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, concat( "LABEL ", node->GetLabel()->GetName() ) ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IAccess* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, concat( "ACCESS ", node->GetName() ) ) );

		leaveNode();
	}

	void IRTreeVisitor::Start( const std::string & filename )
	{
		graphvizOutputFile = std::ofstream( filename );
	}

	void IRTreeVisitor::Close()
	{
		writeGraphToFile();
		graphvizOutputFile.close();
	}

	void IRTreeVisitor::visitNode()
	{
		lastNodeID = currentNodeID;
		currentNodeID = ++numberOfVisitedNodes;
		nodesStack.push( currentNodeID );
		addEdge( lastNodeID, currentNodeID );
	}

	void IRTreeVisitor::leaveNode()
	{
		lastNodeID = currentNodeID;

		nodesStack.pop();

		currentNodeID = nodesStack.top();
	}

	void IRTreeVisitor::addEdge( unsigned int from, unsigned int to )
	{
		edges.push_back( std::make_pair( from, to ) );
	}

	void IRTreeVisitor::writeGraphToFile()
	{
		graphvizOutputFile << "digraph {" << std::endl;

		// nodes
		for( unsigned int i = 0; i < nodeLables.size(); ++i ) {
			graphvizOutputFile << "n" << i << "[ label = \"" << nodeLables[i] << "\" ];" << std::endl;
		}

		// edges
		for( unsigned int i = 0; i < edges.size(); ++i ) {
			graphvizOutputFile << "n" << edges[i].first << " -> n" << edges[i].second << ";" << std::endl;
		}


		graphvizOutputFile << "}";
	}

	unsigned int IRTreeVisitor::createNode()
	{
		return (++numberOfVisitedNodes);
	}

	std::string IRTreeVisitor::concat( const std::string& str, const int n )
	{
		std::stringstream result;
		result << str << n;
		return result.str();
	}
}