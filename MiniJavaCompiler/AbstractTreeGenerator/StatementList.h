#pragma once

#include <memory>
#include "IStatement.h"

namespace AbstractTreeGenerator {
	class CStatementList : public INode {
	public:
		CStatementList( IStatement* theStatement,
			CStatementList* theStatementList = nullptr );
		virtual ~CStatementList();

		virtual void Accept(IVisitor*) override;
		const std::shared_ptr<IStatement> GetStatement() const;
		const std::shared_ptr<CStatementList> GetStatementList() const;
	private:
		std::shared_ptr<IStatement> statement;
		std::shared_ptr<CStatementList> statementList;
	};
}
