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
		const std::shared_ptr<CFrame> frame;
		const std::shared_ptr<CCodeFragment> next;
		const std::shared_ptr<IRTStatement> body;
	};
}