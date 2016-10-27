#pragma once

#include <memory>
#include "MainClass.h"
#include "ClassDeclarationList.h"

namespace AbstractTreeGenerator {
	class CProgram : public INode {
	public:
		CProgram( CMainClass* theMainClass, CClassDeclarationList* theClassDeclarationList );
		virtual ~CProgram();

		virtual void Accept( IVisitor* � ) override;

		const std::shared_ptr<CMainClass> GetMainClass() const;
		const std::shared_ptr<CClassDeclarationList> GetClassDeclarationList() const;
	private:
		std::shared_ptr<CMainClass> mainClass;
		std::shared_ptr<CClassDeclarationList> classDeclarationList;
	};
}
