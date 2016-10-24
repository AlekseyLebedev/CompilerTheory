#pragma once
#include "IdExpression.h"
#include "IStatement.h"
#include <memory>


namespace AbstractTreeGenerator {
	class CMainClass : public INode
	{
	public:
		CMainClass( CIdExpression* theClassName,
			CIdExpression* theArgv,
			IStatement* theStatement );
		virtual ~CMainClass();

		virtual void Accept(IVisitor*) override;

		const std::shared_ptr<CIdExpression> GetClassName() const;
		const std::shared_ptr<CIdExpression> GetArgv() const;
		const std::shared_ptr<IStatement> GetStatement() const;
	private:
		std::shared_ptr<CIdExpression> className;
		std::shared_ptr<CIdExpression> argv;
		std::shared_ptr<IStatement> statement;
	};
}
