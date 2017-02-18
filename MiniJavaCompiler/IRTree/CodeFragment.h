#pragma once
#include <memory>

namespace IRTree {
	class CFrame;
	class IRTStatement;
	class CCodeFragment {
	public:
		CCodeFragment( const std::shared_ptr<IRTStatement> body );
		void SetNext( const std::shared_ptr<CCodeFragment> next );
		const std::shared_ptr<IRTStatement> GetTree() const;
		const std::shared_ptr<CCodeFragment> GetNext() const;
	private:
		std::shared_ptr<CFrame> frame;
		std::shared_ptr<CCodeFragment> next;
		std::shared_ptr<IRTStatement> body;
	};
}