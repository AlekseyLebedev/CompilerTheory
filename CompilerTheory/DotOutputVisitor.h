#pragma once
#include "IVisitor.h"

namespace GraphvizOutput {

	class CDotOutputVisitor : public FirstTask::IVisitor
	{
	public:
		CDotOutputVisitor();
		void Start(std::string filename);
		void Close();
		virtual ~CDotOutputVisitor();

		// Унаследовано через IVisitor
		virtual void Visit(FirstTask::CCompoundStatement *) override;
		virtual void Visit(FirstTask::CPrintStatement *) override;
		virtual void Visit(FirstTask::COperationExpression *) override;
		virtual void Visit(FirstTask::CNumExpression *) override;


	private:
		std::ofstream dotFile;
		size_t id;

		size_t enterNode(const std::string & label);
	};

}