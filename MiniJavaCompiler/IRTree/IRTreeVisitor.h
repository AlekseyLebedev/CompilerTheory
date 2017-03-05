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

		virtual void Visit( const IRTExpList* node ) override;

		// Expressions
		virtual void Visit( const IRTEConst* node ) override;
		virtual void Visit( const IRTEConstBool* node ) override;
		virtual void Visit( const IRTEName* node ) override;
		virtual void Visit( const IRTETemp* node ) override;
		virtual void Visit( const IRTEBinop* node ) override;
		virtual void Visit( const IRTEMem* node ) override;
		virtual void Visit( const IRTECall* node ) override;
		virtual void Visit( const IRTEEseq* node ) override;

		// Statements
		virtual void Visit( const IRTSMove* node ) override;
		virtual void Visit( const IRTSExp* node ) override;
		virtual void Visit( const IRTSJump* node ) override;
		virtual void Visit( const IRTSCjump* node ) override;
		virtual void Visit( const IRTSSeq* node ) override;
		virtual void Visit( const IRTSLabel* node ) override;

		virtual void Visit( const IAccess* node ) override;

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
