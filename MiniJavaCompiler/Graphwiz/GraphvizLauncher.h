#pragma once
#include "..\AbstractTreeGenerator\INode.h"

namespace GraphvizOutput {
	class CGraphvizLauncher {
	public:
		CGraphvizLauncher();
		virtual ~CGraphvizLauncher();
		template <typename TDotVisitor, typename TNode>
		static void Launch( TNode * node, int number );

	private:
		static const char* filename;
		static const char* convertString;
		static const char* launchString;
		static const char* extentionString;
	};

	CGraphvizLauncher::CGraphvizLauncher()
	{
	}


	CGraphvizLauncher::~CGraphvizLauncher()
	{
	}

	template <typename TDotVisitor, typename TNode>
	void CGraphvizLauncher::Launch( TNode * node, int number )
	{
		TDotVisitor visitor;
		visitor.Start( filename );
		node->Accept( &visitor );
		visitor.Close();
		std::stringstream convert;
		convert << convertString << number << extentionString;
		system( convert.str().c_str() );
		convert = std::stringstream();
		convert << launchString << number << extentionString;
		system( convert.str().c_str() );
	}

	const char* CGraphvizLauncher::filename = "temp.dot";
	const char* CGraphvizLauncher::convertString = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng temp.dot -o image";
	const char* CGraphvizLauncher::launchString = "image";
	const char* CGraphvizLauncher::extentionString = ".png";
}
