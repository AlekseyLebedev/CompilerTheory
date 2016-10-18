#pragma once

#include <memory>
#include "Argument.h"

namespace FirstTask {
	class CArgumentList {
	public:
		CArgumentList( std::shared_ptr<CArgument> theArgument, 
			std::shared_ptr<CArgumentList> theArgumentList = nullptr );
		virtual ~CArgumentList();

		//		virtual void Accept(IVisitor*) override;
	private:
		std::shared_ptr<CArgument> argument;
		std::shared_ptr<CArgumentList> argumentList;
	};
}
