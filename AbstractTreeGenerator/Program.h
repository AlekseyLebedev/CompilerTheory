#pragma once

#include <memory>
#include "MainClass.h"
#include "ClassDeclarationList.h"

namespace FirstTask {
	class CProgram {
	public:
		CProgram( std::shared_ptr<CMainClass> theMainClass, std::shared_ptr<CClassDeclarationList> theClassDeclarationList );
		virtual ~CProgram();

		//		virtual void Accept(IVisitor*) override;

	private:
		std::shared_ptr<CMainClass> mainClass;
		std::shared_ptr<CClassDeclarationList> classDeclarationList;
	};
}
