#pragma once
#include "IVisitor.h"

namespace GraphvizOutput {

	class CDotOutputVisitor : public IVisitor
	{
	public:
		CDotOutputVisitor();
		void Start(std::string filename);
		void Close();
		virtual ~CDotOutputVisitor();

	private:
		std::ofstream dotFile;

		// Унаследовано через IVisitor
		virtual void Visit(CCompoundStm *) override;
		virtual void Visit(CPrintStm *) override;
		virtual void Visit(COpExp *) override;
		virtual void Visit(CNumExp *) override;
	};

}