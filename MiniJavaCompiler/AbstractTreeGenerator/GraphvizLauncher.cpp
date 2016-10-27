#include "GraphvizLauncher.h"
#include "DotOutputVisitor.h"
#include <cstdlib>
#include <sstream>

namespace GraphvizOutput {
	CGraphvizLauncher::CGraphvizLauncher()
	{
	}


	CGraphvizLauncher::~CGraphvizLauncher()
	{
	}

	void CGraphvizLauncher::Launch(AbstractTreeGenerator::CProgram * node, int number)
	{
		CDotOutputVisitor visitor;
		visitor.Start(filename);
		node->Accept(&visitor);
		visitor.Close();
		std::stringstream convert;
		convert << convertString << number << extentionString;
		system(convert.str().c_str());
		convert = std::stringstream();
		convert << launchString << number << extentionString;
		system( convert.str().c_str() );
	}

	const char* CGraphvizLauncher::filename = "temp.dot";
	const char* CGraphvizLauncher::convertString = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng temp.dot -o image";
	const char* CGraphvizLauncher::launchString = "image";
	const char* CGraphvizLauncher::extentionString = ".png";
}
