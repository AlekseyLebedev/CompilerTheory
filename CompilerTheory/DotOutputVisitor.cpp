#include "stdafx.h"
#include "DotOutputVisitor.h"


namespace GraphvizOutput {

	CDotOutputVisitor::CDotOutputVisitor()
	{
	}

	void CDotOutputVisitor::Start(std::string filename)
	{
		dotFile.open(filename, std::ios_base::out | std::ios_base::trunc);
		dotFile << "digraph G{\n"
			"\tmain->parse->execute;\n"
			"\tmain->init;\n"
			"}\n";
	}

	void CDotOutputVisitor::Close()
	{
		dotFile.close();
	}


	CDotOutputVisitor::~CDotOutputVisitor()
	{
	}

	void CDotOutputVisitor::Visit(CCompoundStm *)
	{
	}

	void CDotOutputVisitor::Visit(CPrintStm *)
	{
	}

	void CDotOutputVisitor::Visit(COpExp *)
	{
	}

	void CDotOutputVisitor::Visit(CNumExp *)
	{
	}

}