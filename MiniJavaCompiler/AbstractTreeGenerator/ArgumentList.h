#pragma once

#include <memory>
#include "Argument.h"

namespace AbstractTreeGenerator {
	class CArgumentList : public INode {
	public:
		CArgumentList( std::shared_ptr<CArgument> theArgument,
			std::shared_ptr<CArgumentList> theArgumentList = nullptr );
		virtual ~CArgumentList();

		virtual void Accept( IVisitor*v ) override;
	private:
		std::shared_ptr<CArgument> argument;
		std::shared_ptr<CArgumentList> argumentList;
	};
}
