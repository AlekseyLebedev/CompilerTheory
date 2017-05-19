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
		void InsertVariable( int name, std::shared_ptr<IAccess> access, bool argument );
		void InsertTemp( int name ); // TODO
		std::shared_ptr<IAccess> GetDataInfo( int name );
		std::shared_ptr<Label> GetLabel();
		std::shared_ptr<IAccess> GetThisAccess();
		std::shared_ptr<IAccess> GetReturnAccess();
		std::shared_ptr<IAccess> GetFramePointerAccess();
		static const int ThisName;
		static const int ReturnName;
		static const int FramePointerName;
		int VariableOffset();
		int ArgumentOffset();
		int NewTemp();

	private:
		std::shared_ptr<IAccess> thisAccess;
		std::shared_ptr<IAccess> returnAccess;
		std::shared_ptr<IAccess> framePointerAccess;
		std::map<int, std::shared_ptr<IAccess>> variables;
		int className;
		std::shared_ptr<Label> label;
		int argumentCount;
		int variableCount;
		int tempCounter;
	};
}
