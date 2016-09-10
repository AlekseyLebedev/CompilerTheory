#include "stdafx.h"
#include "GraphvizLauncher.h"
#include "DotOutputVisitor.h"

namespace GraphvizOutput {
	CGraphvizLauncher::CGraphvizLauncher()
	{
	}


	CGraphvizLauncher::~CGraphvizLauncher()
	{
	}

	void CGraphvizLauncher::Launch(::INode * node)
	{
		CDotOutputVisitor visitor;
		visitor.Start(filename);
		visitor.Visit(node);
		visitor.Close();
		system(convertString);
		system(launchString);
	}

	const char* CGraphvizLauncher::filename = "temp.dot";
	const char* CGraphvizLauncher::convertString = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng temp.dot -o temp.png";
	const char* CGraphvizLauncher::launchString = "temp.png";
}
