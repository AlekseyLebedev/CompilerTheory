#pragma once
#include <memory>

namespace IRTree {
	class CFrame;
	class IRTStatement;
	class CCodeFragment {
	public:
		CCodeFragment(const IRTStatement* body );
		void SetNext( const CCodeFragment* next );
		const IRTStatement* GetTree() const;
		const CCodeFragment* GetNext() const;
	private:
		const CFrame* frame;
		const IRTStatement* body;
		const CCodeFragment* next;
	};
}