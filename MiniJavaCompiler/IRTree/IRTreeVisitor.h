#pragma once

#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <utility>
#include <map>

#include "IVisitor.h"

// Разобраться, как работает graphviz, а пока создадим текстовый файл.

namespace IRTree {

	class IRTreeVisitor : public IVisitor {
	public:

		IRTreeVisitor(const std::wstring& header);
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

		virtual void Visit( const IAccess* node );

		void Start( const std::wstring& filename );
		void Close();
	private:
		unsigned int currentNodeID;
		unsigned int lastNodeID;
		unsigned int numberOfVisitedNodes;
		std::stack<unsigned int> nodesStack;
		std::wstring header;

		std::vector<std::pair<unsigned int, unsigned int>> edges;
		std::map<unsigned int, std::wstring> nodeLables;

		void visitNode();
		void leaveNode();
		void nullNode();

		void addEdge( unsigned int from, unsigned int to );
		unsigned int createNode();

		std::wstring concat( const std::wstring & str, const int n );

		void writeGraphToFile();

		std::wofstream graphvizOutputFile;


	};
}
