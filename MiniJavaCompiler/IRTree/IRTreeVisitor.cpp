#include <cassert>
#include <sstream>
#include"IRTreeVisitor.h"
#include"IRTreeAllClasses.h"

namespace IRTree {

	IRTreeVisitor::IRTreeVisitor( const std::wstring& _header )
		: currentNodeID( 0 ), numberOfVisitedNodes( 0 ), lastNodeID( 0 ), header( _header )
	{
		nodesStack.push( currentNodeID );
		nodeLables.insert( std::make_pair( currentNodeID, L"Frame" ) );
	}

	IRTreeVisitor::~IRTreeVisitor()
	{
	}

	void IRTreeVisitor::Visit( const IRTExpList* node )
	{
		visitNode();

		const IRTExpression* head = node->GetHead().get();
		const IRTExpList* tail = node->GetTail().get();
		nodeLables.insert( std::make_pair( currentNodeID, L"ELIST" ) );
		if( head ) {
			head->Accept( this );
		}

		if( tail ) {
			tail->Accept( this );
		}

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEConst* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"CONST " + std::to_wstring( node->GetValue() ) ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEName* node )
	{
		visitNode();

		int label = node->GetLabel()->GetName();
		std::wstring labelName = std::to_wstring( label ) + L" (";
		labelName += node->GetLabel()->GetInfo() + L")";
		assert( SL_Count == 3 );
		nodeLables.insert( std::make_pair( currentNodeID, L"NAME " + labelName ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTETemp* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"TEMP " + node->GetTemp()->GetName() ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEBinop* node )
	{
		visitNode();

		switch( node->GetBinop() ) {
			case BINOP_PLUS:
				nodeLables.insert( std::make_pair( currentNodeID, L"PLUS" ) );
				break;
			case BINOP_MINUS:
				nodeLables.insert( std::make_pair( currentNodeID, L"MINUS" ) );
				break;
			case BINOP_MUL:
				nodeLables.insert( std::make_pair( currentNodeID, L"MUL" ) );
				break;
			case BINOP_DIV:
				nodeLables.insert( std::make_pair( currentNodeID, L"DIV" ) );
				break;
			case BINOP_AND:
				nodeLables.insert( std::make_pair( currentNodeID, L"AND" ) );
				break;
			case CJUMP_LT:
				nodeLables.insert( std::make_pair( currentNodeID, L"LESS" ) );
				break;
			case BINOP_MOD:
				nodeLables.insert( std::make_pair( currentNodeID, L"MOD" ) );
				break;
			case BINOP_OR:
				nodeLables.insert( std::make_pair( currentNodeID, L"OR" ) );
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

		nodeLables.insert( std::make_pair( currentNodeID, L"MEM" ) );
		node->GetExp()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTECall* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"CALL" ) );
		node->GetFunc()->Accept( this );

		if( node->GetArgs() ) {
			node->GetArgs()->Accept( this );
		}

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTEEseq* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"ESEQ" ) );
		// left
		if( node->GetStm() ) {
			node->GetStm()->Accept( this );
		}
		// right
		if( node->GetExp() ) {
			node->GetExp()->Accept( this );
		}

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSMove* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"MOVE" ) );
		// left
		node->GetExrDst()->Accept( this );
		// right
		node->GetExrSrc()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSExp* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"EXP" ) );
		node->GetExp()->Accept( this );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSJump* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"JUMP" ) );

		unsigned int tempNode = createNode();
		nodeLables.insert( std::make_pair( tempNode, concat( L"LABEL ", node->GetLabel()->GetName() ) ) );
		addEdge( currentNodeID, tempNode );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSCjump* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"CJUMP" ) );

		unsigned int tempNode = createNode();

		switch( node->GetRelop() ) {
			case CJUMP_EQ:
				nodeLables.insert( std::make_pair( tempNode, L"==" ) );
				break;
			case CJUMP_GE:
				nodeLables.insert( std::make_pair( tempNode, L">=" ) );
				break;
			case CJUMP_GT:
				nodeLables.insert( std::make_pair( tempNode, L">" ) );
				break;
			case CJUMP_LE:
				nodeLables.insert( std::make_pair( tempNode, L"<=" ) );
				break;
			case CJUMP_LT:
				nodeLables.insert( std::make_pair( tempNode, L"<" ) );
				break;
			case CJUMP_NE:
				nodeLables.insert( std::make_pair( tempNode, L"!=" ) );
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
		nodeLables.insert( std::make_pair( tempNode, concat( L"LABEL ", node->GetLabelLeft()->GetName() ) ) );
		addEdge( currentNodeID, tempNode );

		// right label, false
		tempNode = createNode();
		nodeLables.insert( std::make_pair( tempNode, concat( L"LABEL ", node->GetLabelRight()->GetName() ) ) );
		addEdge( currentNodeID, tempNode );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSSeq* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, L"SEQ" ) );
		// left
		if( node->GetStmLeft().get() != 0 ) {
			node->GetStmLeft()->Accept( this );
		} else {
			nullNode();
			assert( node->GetStmRight() == 0 );
		}
		// right
		if( node->GetStmRight() ) {
			node->GetStmRight()->Accept( this );
		} else {
			nullNode();
		}

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IRTSLabel* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, concat( L"LABEL ", node->GetLabel()->GetName() ) ) );

		leaveNode();
	}

	void IRTreeVisitor::Visit( const IAccess* node )
	{
		visitNode();

		nodeLables.insert( std::make_pair( currentNodeID, concat( L"ACCESS ", node->GetName() ) + L" (" + node->GetInfo() + L")" ) );

		leaveNode();
	}

	void IRTreeVisitor::Start( const std::wstring & filename )
	{
		graphvizOutputFile = std::wofstream( filename );
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

	void IRTreeVisitor::nullNode()
	{
		visitNode();
		nodeLables.insert( std::make_pair( currentNodeID, L"NULL" ) );
		leaveNode();
	}

	void IRTreeVisitor::addEdge( unsigned int from, unsigned int to )
	{
		edges.push_back( std::make_pair( from, to ) );
	}

	void IRTreeVisitor::writeGraphToFile()
	{
		graphvizOutputFile << L"digraph {" << std::endl;
		graphvizOutputFile << L"\t label=\"" << header << L"\"" << std::endl;

		// nodes
		for( unsigned int i = 0; i < nodeLables.size(); ++i ) {
			graphvizOutputFile << L"n" << i << L"[ label = \"" << nodeLables[i] << L"\" ];" << std::endl;
		}

		// edges
		for( unsigned int i = 0; i < edges.size(); ++i ) {
			graphvizOutputFile << L"n" << edges[i].first << L" -> n" << edges[i].second << L";" << std::endl;
		}


		graphvizOutputFile << L"}";
	}

	unsigned int IRTreeVisitor::createNode()
	{
		return (++numberOfVisitedNodes);
	}

	std::wstring IRTreeVisitor::concat( const std::wstring& str, const int n )
	{
		std::wstringstream result;
		result << str << n;
		return result.str();
	}
}