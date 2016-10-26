#pragma once
#include "INode.h"

namespace GraphvizOutput {
	class CGraphvizLauncher {
	public:
		CGraphvizLauncher();
		virtual ~CGraphvizLauncher();
		static void Launch( AbstractTreeGenerator::CProgram* node, int number = 0 );

	private:
		static const char* filename;
		static const char* convertString;
		static const char* launchString;
		static const char* extentionString;
	};
}
