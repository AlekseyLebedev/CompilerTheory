#pragma once
#include <memory>
#include <map>

#include "Access.h"


namespace IRTree {
	class IRTExpression;
	class Label;

	class CFrame {
	public:
		CFrame( int className, std::shared_ptr<Label> label );
		void InsertVariable( int name, std::shared_ptr<IAccess> access );
		std::shared_ptr<IAccess> GetDataInfo( int name );
		std::shared_ptr<Label> GetLabel();
		std::shared_ptr<IAccess> GetThisAccess();
		std::shared_ptr<IAccess> GetReturnAccess();
		static const int ThisName;
		static const int ReturnName;

	private:
		std::shared_ptr<IAccess> thisAccess;
		std::shared_ptr<IAccess> returnAccess;
		std::map<int, std::shared_ptr<IAccess>> variables;
		int className;
		std::shared_ptr<Label> label;
	};
}