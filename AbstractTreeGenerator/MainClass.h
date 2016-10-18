#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace FirstTask {
	class CMainClass
	{
	public:
		CMainClass( std::shared_ptr<CIdExpression> theClassName,
			std::shared_ptr<CIdExpression> theArgv,
			std::shared_ptr<IStatement> theStatement );
		virtual ~CMainClass();

//		virtual void Accept(IVisitor*) override;

		std::shared_ptr<CIdExpression> GetName() const;
	private:
		std::shared_ptr<CIdExpression> className;
		std::shared_ptr<CIdExpression> argv;
		std::shared_ptr<IStatement> statement;
	};
}
