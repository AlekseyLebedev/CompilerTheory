#include "GraphvizLauncher.h"
#include "DotOutputVisitor.h"
#include <stdlib.h>

namespace GraphvizOutput {
	CGraphvizLauncher::CGraphvizLauncher()
	{
	}


	CGraphvizLauncher::~CGraphvizLauncher()
	{
	}

	void CGraphvizLauncher::Launch(FirstTask::INode * node)
	{
		CDotOutputVisitor visitor;
		visitor.Start(filename);
		node->Accept(&visitor);
		visitor.Close();
		system(convertString);
		system(launchString);
	}

	const char* CGraphvizLauncher::filename = "temp.dot";
	const char* CGraphvizLauncher::convertString = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng temp.dot -o temp.png";
	const char* CGraphvizLauncher::launchString = "temp.png";
}
