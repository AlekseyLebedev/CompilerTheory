#pragma once
#include <memory>
#include <map>

#include "Access.h"


namespace IRTree {
	class IRTExpression;
	class Label;

	class CFrame {
	public:
		CFrame( int className, Label* label );
		void InsertVariable( int name, std::shared_ptr<IAccess> access );
		IAccess* GetDataInfo( int name );
		Label* GetLabel();
		IAccess* GetThisAccess();
		static const int ThisName;

	private:
		std::shared_ptr<IAccess> thisAccess;
		std::map<int, std::shared_ptr<IAccess>> variables;
		int className;
		std::shared_ptr<Label> label;
	};
}