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

	private:
		std::ofstream dotFile;

		// Унаследовано через IVisitor
		virtual void Visit(FirstTask::CCompoundStm *) override;
		virtual void Visit(FirstTask::CPrintStm *) override;
		virtual void Visit(FirstTask::COpExp *) override;
		virtual void Visit(FirstTask::CNumExp *) override;
	};

}