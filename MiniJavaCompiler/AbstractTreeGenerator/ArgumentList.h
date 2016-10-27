#pragma once

#include <memory>
#include "Argument.h"

namespace AbstractTreeGenerator {
	class CArgumentList : public INode {
	public:
		CArgumentList( CArgument* theArgument, CArgumentList* theArgumentList = nullptr );
		virtual ~CArgumentList();

		const std::shared_ptr<CArgument> GetArgument() const;
		const std::shared_ptr<CArgumentList> GetArgumentList()const;

		virtual void Accept( IVisitor*v ) override;
	private:
		std::shared_ptr<CArgument> argument;
		std::shared_ptr<CArgumentList> argumentList;
	};
}
