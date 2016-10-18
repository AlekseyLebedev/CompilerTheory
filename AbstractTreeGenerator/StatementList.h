#pragma once

#include <memory>
#include "IStatement.h"

namespace FirstTask {
	class CStatementList {
	public:
		CStatementList( std::shared_ptr<IStatement> theStatement,
			std::shared_ptr<CStatementList> theStatementList = nullptr );
		virtual ~CStatementList();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<IStatement> statement;
		std::shared_ptr<CStatementList> statementList;
	};
}
