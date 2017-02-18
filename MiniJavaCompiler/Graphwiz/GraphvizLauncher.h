#pragma once
#include "..\AbstractTreeGenerator\INode.h"

namespace GraphvizOutput {
	class CGraphvizLauncher {
	public:
		CGraphvizLauncher();
		virtual ~CGraphvizLauncher();
		template <typename TDotVisitor, typename TNode>
		static void Launch( TNode * node, int number, const std::wstring& header = L"" );

	private:
		static const wchar_t* filename;
		static const wchar_t* convertString;
		static const wchar_t* launchString;
		static const wchar_t* extentionString;
	};

	CGraphvizLauncher::CGraphvizLauncher()
	{
	}


	CGraphvizLauncher::~CGraphvizLauncher()
	{
	}

	template <typename TDotVisitor, typename TNode>
	void CGraphvizLauncher::Launch( TNode * node, int number, const std::wstring& header )
	{
		TDotVisitor visitor( header );
		visitor.Start( filename );
		node->Accept( &visitor );
		visitor.Close();
		std::wstringstream convert;
		convert << convertString << number << extentionString;
		_wsystem( convert.str().c_str() );
		convert = std::wstringstream();
		convert << launchString << number << extentionString;
		_wsystem( convert.str().c_str() );
	}

	const wchar_t* CGraphvizLauncher::filename = L"temp.dot";
	const wchar_t* CGraphvizLauncher::convertString = L"\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tpng temp.dot -o image";
	const wchar_t* CGraphvizLauncher::launchString = L"image";
	const wchar_t* CGraphvizLauncher::extentionString = L".png";
}
