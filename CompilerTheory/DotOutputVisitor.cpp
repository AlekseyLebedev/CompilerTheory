#include "stdafx.h"
#include "DotOutputVisitor.h"


namespace GraphvizOutput {

	CDotOutputVisitor::CDotOutputVisitor()
	{
	}

	void CDotOutputVisitor::Start(std::string filename)
	{
		dotFile.open(filename, std::ios_base::out | std::ios_base::trunc);
		dotFile << "digraph G{\n";
	}

	void CDotOutputVisitor::Close()
	{
		dotFile << "}\n";
		dotFile.close();
	}


	CDotOutputVisitor::~CDotOutputVisitor()
	{
	}

	void CDotOutputVisitor::Visit(FirstTask::CCompoundStm *)
	{
	}

	void CDotOutputVisitor::Visit(FirstTask::CPrintStm *)
	{
	}

	void CDotOutputVisitor::Visit(FirstTask::COpExp *)
	{
	}

	void CDotOutputVisitor::Visit(FirstTask::CNumExp *)
	{
	}

}